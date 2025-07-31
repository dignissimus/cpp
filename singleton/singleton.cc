#include <iostream>

template
<typename T>
struct Singleton {
  T value;
  Singleton(const Singleton& singleton) : Singleton(singleton.value) {}
  Singleton() {}
  ~Singleton() {}
  Singleton& operator=(const Singleton& singleton) {
    return &*this;
  }
  Singleton(const T value) : value(value) {}

  friend bool operator==(const Singleton& left, const Singleton& right) {
    return left.value == right.value;
  }

  friend bool operator!=(const Singleton& left, const Singleton& right) {
    return !(left == right);
  }

  friend bool operator<(const Singleton& left, const Singleton& right) {
    return left.value < right.value;
  }

  friend bool operator>(const Singleton& left, const Singleton& right) {
    return right < left;
  }

  friend bool operator<=(const Singleton& left, const Singleton& right) {
    return !(right < left);
  }

  friend bool operator>=(const Singleton& left, const Singleton& right) {
    return !(right < left);
  }
};

int main() {
  Singleton<int> singleton{5};
  std::cout << singleton.value << std::endl;
}
