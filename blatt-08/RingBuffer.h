// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Autors: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//         Hannah Bast <bast@cs.uni-freiburg.de>

#pragma once
#include <cstddef> // for size_t
#include <cstdint> // for uint64_t

// A simple ring buffer with a fixed capacity. It stores a sequence of elements,
// to which we can push at the end and pop from the beginning.
template <typename T> class RingBuffer {
private:
  T *data_;
  // The index of the beginning of the stored sequence.
  size_t begin_ = 0;
  size_t size_ = 0;
  size_t capacity_;

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
};

// A specialization of the `RingBuffer` class for elements of type `bool`.
template <> class RingBuffer<bool> {
private:
  uint64_t *data_;
  // The index of the beginning of the stored sequence.
  size_t begin_ = 0;
  size_t size_ = 0;
  size_t capacity_;

public:
  explicit RingBuffer(size_t capacity);
  ~RingBuffer();
  size_t size() const;
  bool isEmpty() const;
  bool isFull() const;
  void push(bool value);

  bool pop();
  RingBuffer(const RingBuffer &) = delete;
  RingBuffer &operator=(const RingBuffer &) = delete;
  // Note: The move operations would be deleted anyway (because we deleted the
  // copy operations), but being explicit is always a good thing.
  RingBuffer(RingBuffer &&) = delete;
  RingBuffer &operator=(RingBuffer &&) = delete;
};
