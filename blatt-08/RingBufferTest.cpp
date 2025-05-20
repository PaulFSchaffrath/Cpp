// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//
//

#include "RingBuffer.h"
#include <cstdlib>
#include <gtest/gtest.h>

// ________________________________
TEST(RingBuffer, CapacityZero) {
  {
    RingBuffer<int> r{0};
    ASSERT_TRUE(r.isFull());
    ASSERT_TRUE(r.isEmpty());
  }
  {
    RingBuffer<bool> r{0};
    ASSERT_TRUE(r.isFull());
    ASSERT_TRUE(r.isEmpty());
  }
}

// ________________________________
TEST(RingBuffer, CapacityOne) {
  {
    RingBuffer<int> r{1};
    ASSERT_FALSE(r.isFull());
    ASSERT_TRUE(r.isEmpty());
    // Repeated cycles of inserts and deletes
    for (size_t i = 0; i < 20; ++i) {
      r.push(i);
      ASSERT_TRUE(r.isFull());
      ASSERT_FALSE(r.isEmpty());
      ASSERT_EQ(i, r.pop());
      ASSERT_FALSE(r.isFull());
      ASSERT_TRUE(r.isEmpty());
    }
  }

  {
    RingBuffer<bool> r{1};
    ASSERT_FALSE(r.isFull());
    ASSERT_TRUE(r.isEmpty());
    // Repeated cycles of inserts and deletes
    for (size_t i = 0; i < 20; ++i) {
      bool value = i % 2 == 0;
      r.push(value);
      ASSERT_TRUE(r.isFull());
      ASSERT_FALSE(r.isEmpty());
      ASSERT_EQ(value, r.pop());
      ASSERT_FALSE(r.isFull());
      ASSERT_TRUE(r.isEmpty());
    }
  }
}

// _______________________________
TEST(RingBufferInt, CapacityTwo) {
  RingBuffer<int> r{2};
  ASSERT_FALSE(r.isFull());
  ASSERT_TRUE(r.isEmpty());
  // Repeated cycles of inserts and deletes
  for (size_t i = 0; i < 20; ++i) {
    r.push(i + 42);
    // Only one element pushed
    ASSERT_FALSE(r.isFull());
    ASSERT_FALSE(r.isEmpty());
    r.push(i + 43);
    ASSERT_TRUE(r.isFull());
    ASSERT_FALSE(r.isEmpty());
    // Both spots are filled.
    ASSERT_EQ(r.pop(), i + 42);
    ASSERT_FALSE(r.isFull());
    ASSERT_FALSE(r.isEmpty());
    // Only the second spot is filled.
    r.push(i + 44);
    ASSERT_TRUE(r.isFull());
    ASSERT_FALSE(r.isEmpty());
    // Both spots are filled, but the first element is in the second spot
    ASSERT_EQ(r.pop(), i + 43);
    ASSERT_FALSE(r.isFull());
    ASSERT_FALSE(r.isEmpty());
    ASSERT_EQ(r.pop(), i + 44);
    ASSERT_FALSE(r.isFull());
    ASSERT_TRUE(r.isEmpty());
  }
}

// Test for different capacities that the RingBuffer<int> and the
// RingBuffer<bool> behave in exactly the same way.
TEST(RingBuffer, RandomTestConsistency) {

  size_t capacities[5] = {0, 1, 15, 100, 256};
  for (size_t i = 0; i < 5; ++i) {
    size_t capacity = capacities[i];
    RingBuffer<int> ints(capacity);
    RingBuffer<bool> bools(capacity);

    // 100'000 random operations
    for (size_t k = 0; k < 100'000; ++k) {
      ASSERT_EQ(ints.isFull(), bools.isFull());
      ASSERT_EQ(ints.isEmpty(), bools.isEmpty());
      bool doPush = (!ints.isFull()) && (ints.isEmpty() || drand48() > 0.5);
      bool doPop = !doPush && !ints.isEmpty();
      if (doPush) {
        bool value = drand48() > 0.5;
        ints.push(value);
        bools.push(value);
      } else if (doPop) {
        ASSERT_EQ(bools.pop(), bool(ints.pop()));
      }
    }
  }
}
