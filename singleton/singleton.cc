#include <concepts>
#include <iostream>
#include <concepts>
#include <functional>

template <typename T>
requires std::strict_weak_order<std::less<T>, T, T>
  && std::copyable<T>
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


template<typename T>
concept SingletonLike = requires(T a, T b) {
  { a == b } -> std::convertible_to<bool>;
  { a < b } -> std::convertible_to<bool>;
  { a.value };
};
static_assert(SingletonLike<Singleton<int>>);

int main() {
  Singleton<int> singleton{5};
  std::cout << singleton.value << std::endl;
}
