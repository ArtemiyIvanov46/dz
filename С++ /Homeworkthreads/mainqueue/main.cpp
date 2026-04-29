#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

#include "timer.h"
//задание1 (тут уже исправленная реализация)
using std::condition_variable;
using std::lock_guard;
using std::mutex;
using std::unique_lock;
using namespace std::chrono_literals;

template <typename T> class threadsafe_stack {
  mutable mutex mtx;
  condition_variable consumers, producers;
  std::vector<T> data;
  int readIdx = 0;
  int writeIdx = -1;
  bool done = false;

public:
  threadsafe_stack() {}
  threadsafe_stack(int size) : data(size) {}
  void push(T value);
  bool wait_and_pop(T &dst);//bool
  void wake_and_done();

private:
  bool full() const noexcept {
    return writeIdx >= static_cast<int>(data.size()) - 1 ;
  }
  bool empty() const noexcept { return writeIdx < 0; }
  bool no_new_tasks() const noexcept { return done; }
};

template <typename T> void threadsafe_stack<T>::push(T value) {
  unique_lock<mutex> lck{mtx};
  producers.wait(lck, [this]() { return !full() || no_new_tasks(); });
  if (no_new_tasks())
    return;
  ++writeIdx;
  data[(writeIdx + readIdx) % data.size()] = value;
  consumers.notify_one();
}

template <typename T> bool threadsafe_stack<T>::wait_and_pop(T &dst) {//теперь бул
  unique_lock<mutex> lck{mtx};
  consumers.wait(lck, [this]() { return !empty() || no_new_tasks(); });
  if (empty())
    return false;
  dst = data[readIdx % data.size()];
  readIdx = (readIdx + 1) % data.size();
  --writeIdx;
  producers.notify_one();
  return true;
}

template <typename T> void threadsafe_stack<T>::wake_and_done() {//раньше done=true было без мьютекса
  {
    lock_guard<mutex> lck{mtx};
    done = true;
  }

  consumers.notify_all();
  producers.notify_all();
}

int num_tasks;
mutex task_mtx;
std::chrono::milliseconds sleep_time_producer;
std::chrono::milliseconds sleep_time_consumer;

void producer(threadsafe_stack<int> &stack) {
  for (;;) {
    int n;
    {
      lock_guard<mutex> lck{task_mtx};
      if (num_tasks <= 0)//теперь создается 1000 задач при нам таскс 1000, а не 1001
        break;
      n = num_tasks;
      --num_tasks;
    }
    std::this_thread::sleep_for(sleep_time_producer);
    stack.push(n);
  }
}

void consumer(threadsafe_stack<int> &stack) {//раньше завершался, если все задачи разобраны, но еще не факт, что отработаны
  for (;;) {
    int n;

    if (!stack.wait_and_pop(n))
      break;

    std::this_thread::sleep_for(sleep_time_consumer);
  }
}

#ifndef NUM_TASKS
#define NUM_TASKS 1000
#endif
#ifndef NUM_CONSUMERS
#define NUM_CONSUMERS 1
#endif
#ifndef NUM_PRODUCERS
#define NUM_PRODUCERS 1
#endif
#ifndef SLEEP_TIME_PRODUCER_MILLISEC
#define SLEEP_TIME_PRODUCER_MILLISEC 1
#endif
#ifndef SLEEP_TIME_CONSUMER_MILLISEC
#define SLEEP_TIME_CONSUMER_MILLISEC 1
#endif

int main() try {
  num_tasks = NUM_TASKS;
  sleep_time_producer = std::chrono::milliseconds(SLEEP_TIME_PRODUCER_MILLISEC);
  sleep_time_consumer = std::chrono::milliseconds(SLEEP_TIME_CONSUMER_MILLISEC);

  std::vector<std::thread> producers;
  std::vector<std::thread> consumers;
  threadsafe_stack<int> stack(100);

  timer::HRTimer t;
  t.start();

  for (int n = 0; n < NUM_PRODUCERS; ++n)
    producers.emplace_back(producer, std::ref(stack));

  for (int n = 0; n < NUM_CONSUMERS; ++n)
    consumers.emplace_back(consumer, std::ref(stack));

  for (auto &p : producers)
    p.join();

  stack.wake_and_done();

  for (auto &c : consumers)
    c.join();

  t.stop();
  std::cout << "Done: " << ": " << t.elapsed() << " millisec" << std::endl;
} catch (const std::runtime_error &err) {
  std::cout << "Runtime error: " << err.what() << "\n";
  return -1;
} catch (...) {
  std::cout << "Unknown error\n";
  return -1;
}//не работает, когда продьюсеров больше, чем консюмеров или когда у них задержка меньше, чем у консьюмеров, то есть, когда
//часто кладут в очередь

