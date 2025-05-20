// Copyright 2024, Paul Schaffrath,
// <ps609@students.uni-freiburg.de>.

#include "RingBuffer.h"

// ___________________________________________________________________________
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  elements_ = new T[capacity];
  capacity_ = capacity;
  size_ = 0u;
  head_ = 0u;
  tail_ = 0u;
}

// ___________________________________________________________________________
template <typename T> RingBuffer<T>::~RingBuffer() { delete[] elements_; }

// ___________________________________________________________________________
template <typename T> void RingBuffer<T>::push(T value) {
  if (!isFull()) {
    elements_[tail_] = value;
    tail_ = (tail_ + 1) % capacity_;
    size_++;
  }
}

template <typename T> T RingBuffer<T>::pop() {
  if (!isEmpty()) {
    T value = elements_[head_];
    head_ = (head_ + 1) % capacity_;
    size_--;
    return value;
  } else
    return T();
}

// ___________________________________________________________________________
template <typename T> size_t RingBuffer<T>::size() const { return size_; }

// ___________________________________________________________________________
template <typename T> size_t RingBuffer<T>::capacity() const {
  return capacity_;
}

// ___________________________________________________________________________
template <typename T> size_t RingBuffer<T>::head() const { return head_; }

// ___________________________________________________________________________
template <typename T> size_t RingBuffer<T>::tail() const { return tail_; }

// ___________________________________________________________________________
template <typename T> T *RingBuffer<T>::elements() const { return elements_; }

// ___________________________________________________________________________
template <typename T> bool RingBuffer<T>::isEmpty() const {
  return size_ == 0u;
}

// ___________________________________________________________________________
template <typename T> bool RingBuffer<T>::isFull() const {
  return size_ == capacity_;
}
template class RingBuffer<int>;
template class RingBuffer<float>;