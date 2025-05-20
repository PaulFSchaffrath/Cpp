// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors:  Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//           Hannah Bast <bast@cs.uni-freiburg.de>
// Modified: Paul Schaffrath <ps609@students.uni-freiburg.de> on 2024-17-06.

#pragma once
#include <cstddef>
#include <gtest/gtest.h>

// A simple ring buffer with a fixed capacity. It stores a sequence of elements,
// to which we can push at the end and pop from the beginning.
template <typename T> class RingBuffer {
public:
  // Create a `RingBuffer` that can store `capacity` many elements at the same
  // time.
  explicit RingBuffer(size_t capacity);

  // Delete the copy and move constructors and assignment operators. We don't
  // need them and the default ones don't do the right thing.
  RingBuffer(const RingBuffer &) = delete;
  RingBuffer &operator=(const RingBuffer &) = delete;
  // Note: The move operations would be deleted anyway (because we deleted the
  // copy operations), but being explicit is always a good thing.
  RingBuffer(RingBuffer &&) = delete;
  RingBuffer &operator=(RingBuffer &&) = delete;

  // Destructor.
  ~RingBuffer();

  // Return the number of elements that are currently stored.
  size_t size() const;

  // Return the capacity of the buffer.
  size_t capacity() const;

  // Return the head of the buffer.
  size_t head() const;

  // Return the tail of the buffer.
  size_t tail() const;

  // Return the elements of the buffer.
  T *elements() const;

  // True if and only if the stored sequence is empty. In this case, it is
  // undefined behavior to call `pop`.
  bool isEmpty() const;

  // True if and only if the buffer is full, because the stored sequence
  // consists of `capacity` many elements. In this case, it is undefined
  // behavior to call `push`.
  bool isFull() const;

  // Add `value` to the end of the stored sequence. This must not be called
  // if the buffer is full, otherwise the behavior is undefined.
  void push(T value);

  // Get the first value of the stored sequence. This must not be called if the
  // buffer is empty, else the behavior is undefined.
  T pop();

private:
  T *elements_;
  size_t size_;
  size_t capacity_;
  size_t head_;
  size_t tail_;
};