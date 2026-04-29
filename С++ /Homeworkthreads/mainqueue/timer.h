#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

namespace chrono = std::chrono;

namespace timer {

template <typename Clock> class Timer {
  typename Clock::time_point begin, end;
  bool started{false};

public:
  Timer() = default;
  void start() {
    started = true;
    begin = Clock::now();
  }
  void stop() {
    started = false;
    end = Clock::now();
  }
  template <typename Duration = std::chrono::milliseconds> unsigned elapsed() {
    auto elapsed = end - begin;
    auto duration = chrono::duration_cast<Duration>(elapsed);
    return duration.count();
  }
};

using HRTimer = Timer<std::chrono::high_resolution_clock>;

} // namespace timer

template <typename Func, typename... Args>
inline void time_it(std::string_view prefix, Func func, Args &&...args) {
  timer::HRTimer t;
  t.start();
  std::invoke(func, std::forward<Args>(args)...);
  t.stop();
  std::cout << prefix << ": " << t.elapsed() << std::endl;
}

