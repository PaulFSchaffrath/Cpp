// Copyright 2024, Paul Schaffrath,
// <ps609@students.uni-freiburg.de>.

#include "./RingBuffer.h"
#include <gtest/gtest.h>

// Test the standard values of the RingBuffer for different types
TEST(RingBufferTest, StandardValues) {
  {
    RingBuffer<float> rb_f(13);
    ASSERT_EQ(13u, rb_f.capacity());
    ASSERT_EQ(0u, rb_f.size());
    ASSERT_EQ(0u, rb_f.head());
    ASSERT_EQ(0u, rb_f.tail());
  }
  {
    RingBuffer<int> rb_i(17);
    ASSERT_EQ(17u, rb_i.capacity());
    ASSERT_EQ(0u, rb_i.size());
    ASSERT_EQ(0u, rb_i.head());
    ASSERT_EQ(0u, rb_i.tail());
  }
}

// Test the push functions
TEST(RingBufferTest, TestPush) {
  // Test for <int>
  {
    RingBuffer<int> rb_i1(5);
    rb_i1.push(1);
    rb_i1.push(24);
    rb_i1.push(13);
    ASSERT_EQ(3u, rb_i1.size());
    ASSERT_EQ(0u, rb_i1.head());
    ASSERT_EQ(3u, rb_i1.tail());
    ASSERT_EQ(1, rb_i1.elements()[0]);
    ASSERT_EQ(24, rb_i1.elements()[1]);
    ASSERT_EQ(13, rb_i1.elements()[2]);
  }
  {
    RingBuffer<int> rb_i2(3);
    rb_i2.push(222);
    rb_i2.push(333);
    rb_i2.push(111);
    ASSERT_EQ(3u, rb_i2.size());
    ASSERT_EQ(0u, rb_i2.head());
    ASSERT_EQ(0u, rb_i2.tail());
    ASSERT_EQ(222, rb_i2.elements()[0]);
    ASSERT_EQ(333, rb_i2.elements()[1]);
    ASSERT_EQ(111, rb_i2.elements()[2]);
  }
  // Test for <float>
  {
    RingBuffer<float> rb_f1(5);
    rb_f1.push(1.1);
    rb_f1.push(24.2);
    rb_f1.push(13.3);
    ASSERT_EQ(3u, rb_f1.size());
    ASSERT_EQ(0u, rb_f1.head());
    ASSERT_EQ(3u, rb_f1.tail());
    ASSERT_FLOAT_EQ(1.1, rb_f1.elements()[0]);
    ASSERT_FLOAT_EQ(24.2, rb_f1.elements()[1]);
    ASSERT_FLOAT_EQ(13.3, rb_f1.elements()[2]);
  }
  {
    RingBuffer<float> rb_f2(4);
    rb_f2.push(222.2);
    rb_f2.push(333.3);
    rb_f2.push(111.1);
    ASSERT_EQ(3u, rb_f2.size());
    ASSERT_EQ(0u, rb_f2.head());
    ASSERT_EQ(3u, rb_f2.tail());
    ASSERT_FLOAT_EQ(222.2, rb_f2.elements()[0]);
    ASSERT_FLOAT_EQ(333.3, rb_f2.elements()[1]);
    ASSERT_FLOAT_EQ(111.1, rb_f2.elements()[2]);
  }
}

// Test the pop functions
TEST(RingBufferTest, TestPop) {
  // Test for <int>
  {
    RingBuffer<int> rb_i1(5);
    rb_i1.push(1);
    rb_i1.push(24);
    rb_i1.push(13);
    ASSERT_EQ(1, rb_i1.pop());
    ASSERT_EQ(2u, rb_i1.size());
    ASSERT_EQ(24, rb_i1.pop());
    ASSERT_EQ(1u, rb_i1.size());
    ASSERT_EQ(13, rb_i1.pop());
    ASSERT_EQ(0u, rb_i1.size());
  }
  {
    RingBuffer<int> rb_i2(3);
    rb_i2.push(222);
    rb_i2.push(333);
    rb_i2.push(111);
    ASSERT_EQ(222, rb_i2.pop());
    ASSERT_EQ(2u, rb_i2.size());
    ASSERT_EQ(333, rb_i2.pop());
    ASSERT_EQ(1u, rb_i2.size());
    ASSERT_EQ(111, rb_i2.pop());
    ASSERT_EQ(0u, rb_i2.size());
  }
  // Test for <float>
  {
    RingBuffer<float> rb_f1(5);
    rb_f1.push(1.1);
    rb_f1.push(24.2);
    rb_f1.push(13.3);
    ASSERT_FLOAT_EQ(1.1, rb_f1.pop());
    ASSERT_EQ(2u, rb_f1.size());
    ASSERT_FLOAT_EQ(24.2, rb_f1.pop());
    ASSERT_EQ(1u, rb_f1.size());
    ASSERT_FLOAT_EQ(13.3, rb_f1.pop());
    ASSERT_EQ(0u, rb_f1.size());
  }
  {
    RingBuffer<float> rb_f2(4);
    rb_f2.push(222.2);
    rb_f2.push(333.3);
    rb_f2.push(111.1);
    ASSERT_FLOAT_EQ(222.2, rb_f2.pop());
    ASSERT_EQ(2u, rb_f2.size());
    ASSERT_FLOAT_EQ(333.3, rb_f2.pop());
    ASSERT_EQ(1u, rb_f2.size());
    ASSERT_FLOAT_EQ(111.1, rb_f2.pop());
    ASSERT_EQ(0u, rb_f2.size());
  }
}

// Test the isFull function
TEST(RingBufferTest, TestIsFull) {
  // Test for <int>
  {
    RingBuffer<int> rb_i1(3);
    rb_i1.push(1);
    rb_i1.push(24);
    rb_i1.push(13);
    ASSERT_TRUE(rb_i1.isFull());
    rb_i1.pop();
    ASSERT_FALSE(rb_i1.isFull());
  }
  {
    RingBuffer<int> rb_i2(2);
    rb_i2.push(222);
    rb_i2.push(333);
    ASSERT_TRUE(rb_i2.isFull());
    rb_i2.pop();
    ASSERT_FALSE(rb_i2.isFull());
  }
  // Test for <float>
  {
    RingBuffer<float> rb_f1(3);
    rb_f1.push(1.1);
    rb_f1.push(24.2);
    rb_f1.push(13.3);
    ASSERT_TRUE(rb_f1.isFull());
    rb_f1.pop();
    ASSERT_FALSE(rb_f1.isFull());
  }
  {
    RingBuffer<float> rb_f2(2);
    rb_f2.push(222.2);
    rb_f2.push(333.3);
    ASSERT_TRUE(rb_f2.isFull());
    rb_f2.pop();
    ASSERT_FALSE(rb_f2.isFull());
  }
}

// Test the isEmpty function
TEST(RingBufferTest, TestIsEmpty) {
  // Test for <int>
  {
    RingBuffer<int> rb_i1(3);
    ASSERT_TRUE(rb_i1.isEmpty());
    rb_i1.push(1);
    ASSERT_FALSE(rb_i1.isEmpty());
    rb_i1.pop();
    ASSERT_TRUE(rb_i1.isEmpty());
  }
  {
    RingBuffer<int> rb_i2(2);
    ASSERT_TRUE(rb_i2.isEmpty());
    rb_i2.push(222);
    ASSERT_FALSE(rb_i2.isEmpty());
    rb_i2.pop();
    ASSERT_TRUE(rb_i2.isEmpty());
  }
  // Test for <float>
  {
    RingBuffer<float> rb_f1(3);
    ASSERT_TRUE(rb_f1.isEmpty());
    rb_f1.push(1.1);
    ASSERT_FALSE(rb_f1.isEmpty());
    rb_f1.pop();
    ASSERT_TRUE(rb_f1.isEmpty());
  }
  {
    RingBuffer<float> rb_f2(2);
    ASSERT_TRUE(rb_f2.isEmpty());
    rb_f2.push(222.2);
    ASSERT_FALSE(rb_f2.isEmpty());
    rb_f2.pop();
    ASSERT_TRUE(rb_f2.isEmpty());
  }
}
