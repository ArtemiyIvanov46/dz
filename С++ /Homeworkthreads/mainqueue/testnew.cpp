#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

#include "threadsafe_stack.h"
//новые тесты, задание 4
using namespace std::chrono_literals;

TEST(ThreadsafeQueueTest, SinglePushSinglePopWorks) {
  threadsafe_stack<int> q(10);

  q.push(42);

  int value = 0;

  ASSERT_TRUE(q.wait_and_pop(value));
  EXPECT_EQ(value, 42);
}

TEST(ThreadsafeQueueTest, QueueWithCapacityOnePreservesOrder) {
  threadsafe_stack<int> q(1);

  std::vector<int> consumed;

  std::thread producer([&]() {
    q.push(1);
    q.push(2);
    q.wake_and_done();
  });

  std::thread consumer([&]() {
    int value = 0;

    while (q.wait_and_pop(value)) {
      consumed.push_back(value);
      std::this_thread::sleep_for(1ms);
    }
  });

  producer.join();
  consumer.join();

  ASSERT_EQ(consumed.size(), 2);
  EXPECT_EQ(consumed[0], 1);
  EXPECT_EQ(consumed[1], 2);
}

TEST(ThreadsafeQueueTest, PushedValuesArePoppedInSameOrder) {
  threadsafe_stack<int> q(3);

  std::vector<int> consumed;

  std::thread producer([&]() {
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.wake_and_done();
  });

  std::thread consumer([&]() {
    int value = 0;

    while (q.wait_and_pop(value)) {
      consumed.push_back(value);
      std::this_thread::sleep_for(1ms);
    }
  });

  producer.join();
  consumer.join();

  ASSERT_EQ(consumed.size(), 4);
  EXPECT_EQ(consumed[0], 10);
  EXPECT_EQ(consumed[1], 20);
  EXPECT_EQ(consumed[2], 30);
  EXPECT_EQ(consumed[3], 40);
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
    int value = 0;

    while (q.wait_and_pop(value)) {
      {
        std::lock_guard<std::mutex> lock(consumed_mtx);
        consumed.push_back(value);
      }

      std::this_thread::sleep_for(1ms);
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
