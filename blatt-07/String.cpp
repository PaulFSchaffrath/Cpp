// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//
#include "./String.h"

// __________________________________________________________________________
String::String(const String &s) {
  size_ = s.size_;
  data_ = new char[size_ + 1];
  for (size_t i = 0; i <= size_; ++i) {
    data_[i] = s.data_[i];
  }
}

// __________________________________________________________________________
String &String::operator=(const String &s) {
  if (this == &s) {
    return *this;
  }
  size_ = s.size_;
  delete[] data_;
  data_ = new char[size_ + 1];
  for (size_t i = 0; i <= size_; ++i) {
    data_[i] = s.data_[i];
  }
  return *this;
}

// ___________________________________________________________________________
String::String(String &&s) {
  data_ = s.data_;
  size_ = s.size_;
  s.data_ = nullptr;
  s.size_ = 0;
}

// __________________________________________________________________________
String &String::operator=(String &&s) {
  if (this == &s) {
    return *this;
  }
  delete[] data_;
  data_ = s.data_;
  size_ = s.size_;
  s.data_ = nullptr;
  s.size_ = 0;
  return *this;
}

// __________________________________________________________________________
String &String::operator=(const char *s) {
  if (s == data_) {
    return *this;
  }
  delete[] data_;
  size_ = strlen(s);
  data_ = new char[size_ + 1];
  for (size_t i = 0; i <= size_; ++i) {
    data_[i] = s[i];
  }
  return *this;
}

// _________________________________________________________________________
void StringSorter::sortWithMove() {
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j + i + 1 < size_; ++j) {
      if (strcmp(strings_[j].c_str(), strings_[j + 1].c_str()) > 0) {
        swapWithMove(j, j + 1);
      }
    }
  }
}

// _________________________________________________________________________
void StringSorter::sortWithCopy() {
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j + i + 1 < size_; ++j) {
      if (strcmp(strings_[j].c_str(), strings_[j + 1].c_str()) > 0) {
        swapWithCopy(j, j + 1);
      }
    }
  }
}
