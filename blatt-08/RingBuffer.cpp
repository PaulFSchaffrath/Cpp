// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//
#include "RingBuffer.h"
#include <utility> // std::move

// ____________________________________________________________________________
template <typename T>
RingBuffer<T>::RingBuffer(size_t capacity)
    : data_{new T[capacity]}, capacity_{capacity} {}

// ____________________________________________________________________________
template <typename T> RingBuffer<T>::~RingBuffer() { delete[] data_; }

// ____________________________________________________________________________
template <typename T> size_t RingBuffer<T>::size() const { return size_; }

// ____________________________________________________________________________
template <typename T> bool RingBuffer<T>::isEmpty() const {
  return size() == 0;
}

// ____________________________________________________________________________
template <typename T> bool RingBuffer<T>::isFull() const {
  return size() == capacity_;
}

// ____________________________________________________________________________
template <typename T> void RingBuffer<T>::push(T value) {
  size_t index = (begin_ + size()) % capacity_;
  data_[index] = std::move(value);
  ++size_;
}

// ____________________________________________________________________________
template <typename T> T RingBuffer<T>::pop() {
  size_t index = begin_;
  begin_ = (begin_ + 1) % capacity_;
  --size_;
  return std::move(data_[index]);
}

// Explicit instantiations for int and float.
template class RingBuffer<int>;
template class RingBuffer<float>;

// ____________________________________________________________________________
RingBuffer<bool>::RingBuffer(size_t capacity)
    : data_{new uint64_t[(capacity + 63) / 64]{}}, capacity_{capacity} {}

// ____________________________________________________________________________
RingBuffer<bool>::~RingBuffer() { delete[] data_; }

// ____________________________________________________________________________
size_t RingBuffer<bool>::size() const { return size_; }

// ____________________________________________________________________________
bool RingBuffer<bool>::isEmpty() const { return size() == 0; }

// ____________________________________________________________________________
bool RingBuffer<bool>::isFull() const { return size() == capacity_; }

// ____________________________________________________________________________
void RingBuffer<bool>::push(bool value) {
  size_t logicalIndex = (begin_ + size()) % capacity_;
  size_t index = logicalIndex / 64;
  size_t bitIndex = logicalIndex % 64;
  uint64_t mask = uint64_t(1) << bitIndex;
  if (value) {
    data_[index] |= mask;
  } else {
    data_[index] &= ~mask;
  }
  ++size_;
}

// ____________________________________________________________________________
bool RingBuffer<bool>::pop() {
  size_t logicalIndex = begin_;
  begin_ = (begin_ + 1) % capacity_;
  --size_;
  size_t index = logicalIndex / 64;
  size_t bitIndex = logicalIndex % 64;
  uint64_t mask = uint64_t(1) << bitIndex;
  return data_[index] & mask;
}
