#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::mutex mtx;
std::condition_variable cv;

enum class Phase {
    T1_TO_CENTER,
    T2_TO_RIGHT,
    T2_TO_CENTER,
    T1_TO_LEFT
};

Phase phase = Phase::T1_TO_CENTER;

const int WIDTH = 8;
const int CYCLES = 3;

void print_frame(int left_pos, int right_pos, const std::string& note = "") {
    std::string left(WIDTH, '-');
    std::string right(WIDTH, '-');

    if (left_pos >= 0) {
        left[left_pos] = 'o';
    }
    if (right_pos >= 0) {
        right[right_pos] = 'o';
    }

    std::cout << "T1 " << left << "|" << right << " T2";
    if (!note.empty()) {
        std::cout << " (" << note << ")";
    }
    std::cout << '\n';

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void t1_worker() {
    for (int cycle = 0; cycle < CYCLES; ++cycle) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return phase == Phase::T1_TO_CENTER; });
        }

        for (int i = 0; i < WIDTH; ++i) {
            print_frame(i, -1, (i == WIDTH - 1 ? "T1 notified T2" : ""));
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            phase = Phase::T2_TO_RIGHT;
        }
        cv.notify_one();

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return phase == Phase::T1_TO_LEFT; });
        }

        for (int i = WIDTH - 1; i >= 0; --i) {
            print_frame(i, -1, (i == 0 ? "T1 finished return" : ""));
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            phase = Phase::T1_TO_CENTER;
        }
        cv.notify_one();
    }
}

void t2_worker() {
    for (int cycle = 0; cycle < CYCLES; ++cycle) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return phase == Phase::T2_TO_RIGHT; });
        }

        for (int i = 0; i < WIDTH; ++i) {
            print_frame(-1, i, (i == WIDTH - 1 ? "T2 notified T1" : ""));
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            phase = Phase::T2_TO_CENTER;
        }
        cv.notify_one();

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return phase == Phase::T2_TO_CENTER; });
        }

        for (int i = WIDTH - 1; i >= 0; --i) {
            print_frame(-1, i, (i == 0 ? "T2 finished" : ""));
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            phase = Phase::T1_TO_LEFT;
        }
        cv.notify_one();
    }
}

int main() {
    std::thread t1(t1_worker);
    std::thread t2(t2_worker);

    t1.join();
    t2.join();

    return 0;
}
