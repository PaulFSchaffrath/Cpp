// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//
#include "./String.h"

// ___________________________________________________________________________
String::String(const String &s) {
  size_ = s.size_;
  // Optimization for empty other string (not needed for Ü6)
  if (size_ == 0) {
    data_ = nullptr;
    return;
  }
  data_ = new char[s.size() + 1];
  for (size_t i = 0; i <= s.size(); ++i) {
    data_[i] = s.data_[i];
  }
}

// ___________________________________________________________________________
String &String::operator=(const String &s) {
  if (this == &s) {
    return *this;
  }
  delete[] data_;
  size_ = s.size_;
  // Optimization for empty other string (not needed for Ü6)
  if (size_ == 0) {
    data_ = nullptr;
    return *this;
  }
  data_ = new char[s.size() + 1];
  for (size_t i = 0; i <= s.size(); ++i) {
    data_[i] = s.data_[i];
  }
  return *this;
}

// ___________________________________________________________________________
String &String::operator=(const char *s) {
  if (s == data_) {
    return *this;
  }
  delete[] data_;
  // Compute the size (without the trailing 0);
  size_ = 0;
  while (s[size_] != '\0') {
    ++size_;
  }
  // Optimization for empty other string (not needed for Ü6)
  if (size_ == 0) {
    data_ = nullptr;
    return *this;
  }
  data_ = new char[size_ + 1];
  for (size_t i = 0; i <= size_; ++i) {
    data_[i] = s[i];
  }
  return *this;
}

// ___________________________________________________________________________
const char *String::c_str() const {
  // If size() == 0, data_ is still nullptr, which is not a valid
  // null-terminated string.
  return size() != 0 ? data_ : "";
}

// ___________________________________________________________________________
StringSorter::StringSorter(const StringSorter &other) {
  size_ = other.size_;
  if (size_ == 0) {
    strings_ = nullptr;
    return;
  }
  strings_ = new String[size_];
  for (size_t i = 0; i < size_; ++i) {
    strings_[i] = other.strings_[i];
  }
}

// ___________________________________________________________________________
StringSorter &StringSorter::operator=(const StringSorter &other) {
  if (this == &other) {
    return *this;
  }
  delete[] strings_;
  size_ = other.size_;
  if (size_ == 0) {
    strings_ = nullptr;
    return *this;
  }
  strings_ = new String[size_];
  for (size_t i = 0; i < size_; ++i) {
    strings_[i] = other.strings_[i];
  }
  return *this;
}

// ___________________________________________________________________________
void StringSorter::sort() {
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j + i + 1 < size_; ++j) {
      if (strcmp(strings_[j].c_str(), strings_[j + 1].c_str()) > 0) {
        swap(j, j + 1);
      }
    }
  }
}

// ___________________________________________________________________________
void StringSorter::swap(size_t i, size_t j) {
  String tmp = strings_[i];
  strings_[i] = strings_[j];
  strings_[j] = tmp;
}
