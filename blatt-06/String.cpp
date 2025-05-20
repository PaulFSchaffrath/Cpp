
#include "String.h"

String::String() {
  size_ = 0;
  c_str_ = new char[size_];
  c_str_[0] = '\0';
}

String::String(const String &other) {
  c_str_ = new char[other.size_];
  for (size_t i = 0; i < other.size_; i++) {
    c_str_[i] = other.c_str_[i];
  }
  size_ = other.size_;
}

String::~String() { delete[] c_str_; }

char &String::operator[](int index) { return c_str_[index]; }

void String::operator=(const String &other) {
  delete[] c_str_;
  c_str_ = new char[other.size_];
  for (size_t i = 0; i < other.size_; i++) {
    c_str_[i] = other.c_str_[i];
  }
  size_ = other.size_;
}

void String::operator=(const char *other) {
  delete[] c_str_;
  size_ = 0;
  for (size_t i = 0; other[i] != '\0'; i++) {
    size_++;
  }
  c_str_ = new char[size_];
  for (size_t i = 0; i < size_; i++) {
    c_str_[i] = other[i];
  }
  c_str_[size_] = '\0';
}

size_t String::size() const { return size_; }

char *String::c_str() const {
  if ((c_str_ == nullptr) || (size_ == 0)) {
    return nullptr;
  }
  return c_str_;
}

StringSorter::StringSorter(size_t size) {
  size_ = size;
  strings_ = new String[size];
}

size_t StringSorter::size() const { return size_; }

void StringSorter::swap(size_t a, size_t b) const {
  String temp = strings_[a];
  strings_[a] = strings_[b];
  strings_[b] = temp;
}

// Implement Bubblesort algorithm to sort the strings in the array for length
// with use of string_.swap
void StringSorter::sort() const {
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_ - i - 1; j++) {
      if (strings_[j].size() > strings_[j + 1].size()) {
        swap(j, j + 1);
      }
    }
  }
}

String &StringSorter::operator[](size_t index) const { return strings_[index]; }
