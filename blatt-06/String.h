#include <cstdio>
#include <cstdlib>

class String {
private:
  char *c_str_;
  size_t size_;

public:
  explicit String();

  String(const String &other);

  ~String();

  void operator=(const String &other);

  void operator=(const char *other);

  char &operator[](int index);

  size_t size() const;

  char *c_str() const;
};

class StringSorter {
private:
  size_t size_ = 0;

public:
  String *strings_ = nullptr;

  explicit StringSorter(size_t size);

  size_t size() const;

  void swap(size_t a, size_t b) const;

  void sort() const;

  // subscript operator
  String &operator[](size_t index) const;
};
