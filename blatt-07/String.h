// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#pragma once

#include <cstring>
#include <gtest/gtest.h>
#include <utility>

// A simple string class.
class String {
private:
  char *data_ = nullptr;
  size_t size_ = 0;

public:
  String() = default;
  ~String() { delete[] data_; }
  size_t size() const { return size_; }

  // Move constructor.
  String(String &&s);

  // Copy constructor.
  String(const String &s);

  // Move assignment.
  String &operator=(String &&s);

  // Copy assignment.
  String &operator=(const String &s);

  // Assignment from C-style string.
  String &operator=(const char *s);

  // Return a C-style string.
  const char *c_str() const { return size() != 0 ? data_ : ""; }
};

// Sort a number of strings.
class StringSorter {
private:
  String *strings_;
  size_t size_;

public:
  // Construct n empty strings and store them
  explicit StringSorter(size_t n) {
    strings_ = new String[n];
    size_ = n;
  }

  size_t size() const { return size_; }
  ~StringSorter() { delete[] strings_; }

  // Access the i-th String
  String &operator[](size_t i) { return strings_[i]; }

  // Access the i-th String but read-only
  const String &operator[](size_t i) const { return strings_[i]; }

  // A simple sort (using highly efficient bubble sort).

  // Sort using the move assignment and constructor for swapping
  void sortWithMove();

  // Sort using the copy assignment and constructor for swapping
  void sortWithCopy();

private:
  // Swap the i-th and j-th string using move semantics.
  void swapWithMove(size_t i, size_t j) {
    String tmp = std::move(strings_[i]);
    strings_[i] = std::move(strings_[j]);
    strings_[j] = std::move(tmp);
  }
  FRIEND_TEST(StringSorter, SwapWithMove);

  // Swap the i-th and j-th string using copy semantics.
  void swapWithCopy(size_t i, size_t j) {
    String tmp = strings_[i];
    strings_[i] = strings_[j];
    strings_[j] = tmp;
  }
  FRIEND_TEST(StringSorter, SwapWithCopy);
};
