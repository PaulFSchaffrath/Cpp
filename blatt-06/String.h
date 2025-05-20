// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//
#pragma once

#include <gtest/gtest.h>

// A simple string class.
class String {
private:
  char *data_ = nullptr;
  size_t size_ = 0;

public:
  // The members are already initialized.
  String() = default;

  // Destructor. Note that data_ might be the nullptr,
  // but deleting the nullptr is allowed (it does nothing).
  ~String() { delete[] data_; }

  size_t size() const { return size_; }

  // Copy constructor.
  String(const String &s);

  // Copy assignment.
  String &operator=(const String &s);

  // Assignment from C-style string.
  String &operator=(const char *s);

  // Return a C-style string.
  const char *c_str() const;
};

// Sort a number of strings.
class StringSorter {
private:
  String *strings_ = nullptr;
  size_t size_ = 0;

public:
  // Default construct an array of n strings.
  explicit StringSorter(size_t n) {
    // The default constructor is called for each of the strings.
    strings_ = new String[n];
    size_ = n;
  }

  // Return the number of Strings.
  size_t size() const { return size_; }

  // Copy constructor and copy assignment.
  // Not needed for blatt-06 but necessary to fulfill the
  // Rule of Three and they might come in handy for blatt-07
  StringSorter(const StringSorter &other);
  StringSorter &operator=(const StringSorter &other);
  // Destructor
  ~StringSorter() { delete[] strings_; }

  // Return a non-const reference to the i-th String.
  String &operator[](size_t i) { return strings_[i]; }

  // Sort the strings (using highly efficient bubble sort).
  void sort();

private:
  // Swap the Strings at positions i and j
  void swap(size_t i, size_t j);
  FRIEND_TEST(StringSorter, Swap);
};
