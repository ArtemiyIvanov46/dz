#include <future>
#include <iostream>
#include <stdexcept>
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



int main() {
    std::vector<int> v{1, 2, 3, 4};

    auto res = map_reduce_parallel(
        v.begin(), v.end(),
        [](int x) { return x * 2; },
        [](int a, int b) { return a + b; },
        2
    );
    auto res2 = map_reduce_parallel(
        v.cbegin(), v.cend(),
        [](int x) { return x * 2; },
        [](int a, int b) { return a + b; },
        2
    );
    std::cout << res << '\n' << res2 << '\n'; // 20
}
