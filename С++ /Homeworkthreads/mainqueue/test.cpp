//Задание2
//#include <gtest/gtest.h>

// Demonstrate some basic assertions.
//TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
//  EXPECT_STRNE("hello", "world");
  // Expect equality.
//  EXPECT_EQ(7 * 6, 42);
//}
//Test project /Users/rootadmin/Desktop/Информатика/С++ /Homeworkthreads/mainqueue/build
//    Start 1: HelloTest.BasicAssertions
//1/1 Test #1: HelloTest.BasicAssertions ........   Passed    0.01 sec
//
//100% tests passed, 0 tests failed out of 1
//
//Total Test time (real) =   0.01 sec

#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <mutex>
#include <set>
#include <thread>
#include <vector>

#include "threadsafe_stack.h"
//Тесты для старой реализации
using namespace std::chrono_literals;

TEST(ThreadsafeQueueTest, SinglePushSinglePopWorks) {
  threadsafe_stack<int> q(10);

  q.push(42);

  int value = 0;
  q.wait_and_pop(value);

  EXPECT_EQ(value, 42);
}

TEST(ThreadsafeQueueTest, QueueWithCapacityOneMustNotOverwriteData) {
  threadsafe_stack<int> q(1);

  q.push(1);
  q.push(2);

  int first = 0;
  int second = 0;

  q.wait_and_pop(first);
  q.wait_and_pop(second);

  EXPECT_EQ(first, 1);
  EXPECT_EQ(second, 2);
}

TEST(ThreadsafeQueueTest, PushedValuesMustBePoppedInSameOrder) {
  threadsafe_stack<int> q(3);

  q.push(10);
  q.push(20);
  q.push(30);
  q.push(40);

  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;

  q.wait_and_pop(a);
  q.wait_and_pop(b);
  q.wait_and_pop(c);
  q.wait_and_pop(d);

  EXPECT_EQ(a, 10);
  EXPECT_EQ(b, 20);
  EXPECT_EQ(c, 30);
  EXPECT_EQ(d, 40);
}
TEST(ThreadsafeQueueTest, ManyProducersOneConsumerShouldNotLoseTasks) {
  constexpr int producers_count = 4;
  constexpr int tasks_per_producer = 250;
  constexpr int total_tasks = producers_count * tasks_per_producer;

  threadsafe_stack<int> q(20);

  std::vector<int> consumed;
  std::mutex consumed_mtx;

  std::vector<std::thread> producers;

  for (int p = 0; p < producers_count; ++p) {
    producers.emplace_back([&, p]() {
      for (int i = 0; i < tasks_per_producer; ++i) {
        q.push(p * tasks_per_producer + i);
      }
    });
  }

  std::thread consumer([&]() {
    while (true) {
      int value = -1;
      q.wait_and_pop(value);

      if (value == -1)
        break;

      {
        std::lock_guard<std::mutex> lock(consumed_mtx);
        consumed.push_back(value);
      }

      std::this_thread::sleep_for(1ms);

      if (consumed.size() >= total_tasks)
        break;
    }
  });

  for (auto &p : producers) {
    p.join();
  }

  q.wake_and_done();

  consumer.join();

  std::sort(consumed.begin(), consumed.end());

  ASSERT_EQ(consumed.size(), total_tasks);

  for (int i = 0; i < total_tasks; ++i) {
    EXPECT_EQ(consumed[i], i);
  }
}
//выводы, задание 3
//25% tests passed, 3 tests failed out of 4

//Total Test time (real) =   1.36 sec

//The following tests FAILED:
//      2 - ThreadsafeQueueTest.QueueWithCapacityOneMustNotOverwriteData (Failed)
//      3 - ThreadsafeQueueTest.PushedValuesMustBePoppedInSameOrder (Failed)
//      4 - ThreadsafeQueueTest.ManyProducersOneConsumerShouldNotLoseTasks (Failed)
//Errors while running CTest
//это на старой реализации

