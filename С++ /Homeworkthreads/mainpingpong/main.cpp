#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool ping_turn = true;

void ping() {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return ping_turn; });

        std::cout << "ping\n";
        ping_turn = false;

        lock.unlock();
        cv.notify_one();
    }
}

void pong() {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !ping_turn; });

        std::cout << "pong\n";
        ping_turn = true;

        lock.unlock();
        cv.notify_one();
    }
}

int main() {
    std::thread t1(ping);
    std::thread t2(pong);

    t1.join();
    t2.join();
}
