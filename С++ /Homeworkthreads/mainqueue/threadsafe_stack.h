#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <utility>
#include <vector>
//задание 4
using std::condition_variable;
using std::lock_guard;
using std::mutex;
using std::unique_lock;

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
//Test project /Users/rootadmin/Desktop/Информатика/С++ /Homeworkthreads/mainqueue/build
//Start 1: ThreadsafeQueueTest.SinglePushSinglePopWorks
//1/4 Test #1: ThreadsafeQueueTest.SinglePushSinglePopWorks .....................   Passed    0.01 sec
//Start 2: ThreadsafeQueueTest.QueueWithCapacityOnePreservesOrder
//2/4 Test #2: ThreadsafeQueueTest.QueueWithCapacityOnePreservesOrder ...........   Passed    0.01 sec
//Start 3: ThreadsafeQueueTest.PushedValuesArePoppedInSameOrder
//3/4 Test #3: ThreadsafeQueueTest.PushedValuesArePoppedInSameOrder .............   Passed    0.01 sec
//Start 4: ThreadsafeQueueTest.ManyProducersOneConsumerShouldNotLoseTasks
//4/4 Test #4: ThreadsafeQueueTest.ManyProducersOneConsumerShouldNotLoseTasks ...   Passed    1.28 sec

//100% tests passed, 0 tests failed out of 4

//Total Test time (real) =   1.32 sec
//(base) MacBook-Air-Ila:mainqueue rootadmin$
