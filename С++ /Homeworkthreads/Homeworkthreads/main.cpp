#include <chrono>
#include <future>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <thread>
#include <vector>
#include <iterator>


template <typename It, typename F1, typename F2>
auto map_reduce(It begin, It end, F1 f1, F2 f2, int num) {
    auto res=f1(*begin);
    ++begin;
    for (It i=begin; i!=end; i++) {
        auto two=f1(*i);
        res=f2(res,two);
    }
    return res;
}

template <typename It, typename F1, typename F2>
auto map_reduce_parallel(It begin, It end, F1 f1, F2 f2, int num) {
    if (begin == end) {
        throw std::invalid_argument("пустой список");
    }

    if (num <= 0) {
        throw std::invalid_argument("не может быть отрицательное количество потоков");
    }

    auto len = std::distance(begin, end);
    if (num > len) {
        num = static_cast<int>(len);
    }

    using Result = decltype(f1(*begin));
    std::vector<std::future<Result>> futures;
    futures.reserve(num);

    for (int t = 0; t < num; ++t) {
        It part_begin = begin;
        It part_end = begin;

        std::advance(part_begin, (len * t) / num);
        std::advance(part_end,   (len * (t + 1)) / num);

        futures.push_back(std::async(
            std::launch::async,
            [part_begin, part_end, f1, f2]() {
                return map_reduce(part_begin, part_end, f1, f2, 1);
            }
        ));
    }

    auto res = futures[0].get();
    for (int i = 1; i < num; ++i) {
        res = f2(res, futures[i].get());
    }

    return res;
}


template <typename It, typename F1, typename F2>
auto map_reduce_thread(It begin, It end, F1 f1, F2 f2, int num) {
    if (begin == end) {
        throw std::invalid_argument("пустой список");
    }

    if (num <= 0) {
        throw std::invalid_argument("слишком мало потоков");
    }

    auto len = std::distance(begin, end);
    if (num > len) {
        num = static_cast<int>(len);
    }

    using Result = decltype(f1(*begin));

    std::vector<std::thread> threads;
    std::vector<std::optional<Result>> partial(num);

    threads.reserve(num);

    for (int t = 0; t < num; ++t) {
        It part_begin = begin;
        It part_end = begin;

        std::advance(part_begin, (len * t) / num);
        std::advance(part_end,   (len * (t + 1)) / num);

        threads.emplace_back(
            [part_begin, part_end, f1, f2, &partial, t]() {
                partial[t] = map_reduce(part_begin, part_end, f1, f2, 1);
            }
        );
    }

    for (auto& th : threads) {
        th.join();
    }

    Result res = *partial[0];
    for (int i = 1; i < num; ++i) {
        res = f2(res, *partial[i]);
    }

    return res;
}

template <typename It, typename F1, typename F2>

auto map_reduce_thread_strided(It begin, It end, F1 f1, F2 f2, int num) {
    if (begin == end) {
        throw std::invalid_argument("пустой список");
    }
    if (num <= 0) {
        throw std::invalid_argument("слишком мало потоков");
    }
    auto len = std::distance(begin, end);
    if (num > len) {
        num = static_cast<int>(len);
    }
    using Result = decltype(f1(*begin));
    std::vector<std::thread> threads;
    std::vector<std::optional<Result>> partial(num);
    threads.reserve(num);
    for (int t = 0; t < num; ++t) {
        threads.emplace_back([=, &partial]() {
            bool first = true;
            Result local{};
            for (decltype(len) i = t; i < len; i += num) {
                auto value = f1(*(begin + i));
                if (first) {
                    local = value;
                    first = false;
                } else {
                    local = f2(local, value);
                }
            }
            if (!first) {
                partial[t] = local;
            }
        });
    }
    for (auto& th : threads) {
        th.join();
    }
    int first_filled = 0;
    while (first_filled < num && !partial[first_filled].has_value()) {
        ++first_filled;
    }
    if (first_filled == num) {
        throw std::runtime_error("не удалось вычислить результат");
    }
    Result res = *partial[first_filled];
    for (int i = first_filled + 1; i < num; ++i) {
        if (partial[i].has_value()) {
            res = f2(res, *partial[i]);
        }
    }
    return res;
}

int main() {
    std::vector<int> v1{1, 2, 3, 4};

    auto res = map_reduce_parallel(
        v1.begin(), v1.end(),
        [](int x) { return x * 2; },
        [](int a, int b) { return a + b; },
        2
    );
    auto res22 = map_reduce_thread(
        v1.cbegin(), v1.cend(),
        [](int x) { return x * 2; },
        [](int a, int b) { return a + b; },
        2
    );
    std::cout << res << '\n' << res22 << '\n'; // 20
    
    
    const int n = 10'000'000;
    const int num_threads = 4;
    std::vector<int> v(n);

    for (int i = 0; i < n; ++i) {
            v[i] = i + 1;
        }
    auto f1 = [](int x) { return static_cast<long long>(x) * x; };
    auto f2 = [](long long a, long long b) { return a + b; };
    
    auto t1_start = std::chrono::steady_clock::now();
    auto res1 = map_reduce_thread(v.begin(), v.end(), f1, f2, num_threads);
    auto t1_end = std::chrono::steady_clock::now();
    
    auto t2_start = std::chrono::steady_clock::now();
    auto res2 = map_reduce_thread_strided(v.begin(), v.end(), f1, f2, num_threads);
    auto t2_end = std::chrono::steady_clock::now();
    
    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(t1_end - t1_start).count();//порядка 16 миллисекунд
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2_end - t2_start).count();//поряда 25 миллисекунд, ответы одинаковые
    std::cout << "Разбиение по диапазонам: " << res1 << ", time = " << ms1 << " ms\n";
    std::cout << "Чередование индексов:   " << res2 << ", time = " << ms2 << " ms\n";
}
