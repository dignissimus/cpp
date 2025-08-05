#include <iostream>
#include <concepts>
#include <format>
#include <functional>

template
<typename T, typename Compare=std::less<T>>
requires std::strict_weak_order<Compare, T, T>
const T& min(const T& left, const T& right, Compare compare) noexcept(noexcept(compare(left, right))) {
  if (compare(left, right)) {
    return left;
  }
  return right;
}

template
<typename T, typename Compare=std::less<T>>
requires std::strict_weak_order<Compare, T, T>
const T& min(const T& left, const T& right) noexcept(noexcept(min(left, right, Compare{}))) {
  return min(left, right, Compare{});
}

template
<typename T, typename Compare=std::less<T>>
const T& max(const T& left, const T& right, Compare compare) noexcept(noexcept(compare(left, right))) {
  if (compare(left, right)) {
    return right;
  }
  return left;
}

template
<typename T>
struct less {
  bool operator()(const T& left, const T& right) {
    return left < right;
  }
};

template
<typename T, typename Compare=std::less<T>>
requires std::strict_weak_order<Compare, T, T>
void sort2(T& left, T& right, Compare compare) {
  if (compare(right, left)) {
    std::swap(left, right);
  }
}

template
<typename T, typename Compare=std::less<T>>
requires std::strict_weak_order<Compare, T, T>
void sort2(T& left, T& right) {
  sort2(left, right, Compare{});
}

int main() {
  int a{1}, b{2};
  int c{3}, d{2};
  std::cout << std::format("min({}, {}) = {}", a, b, min(a, b)) << std::endl;
  std::cout << std::format("min<int, less<int>>({}, {}) = {}", a, b, min<int, less<int>>(a, b)) << std::endl;
  std::cout << std::format("min<int, less<int>>({}, {}) = {}", a, b, min<int, less<int>>(a, b)) << std::endl;
  sort2(c, d);
  std::cout << std::format("After swapping: c={}, d={}", c, d) << std::endl;
}
