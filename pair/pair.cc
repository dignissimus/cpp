#include <iostream>
#include <concepts>

template
<typename T, typename U>
requires
std::copyable<T>
&& std::copyable<U>
&& std::strict_weak_order<std::less<T>, T, T>
&& std::strict_weak_order<std::less<U>, U, U>
&& std::equality_comparable<T>
&& std::equality_comparable<U>
struct Pair{
  T first;
  U second;

  Pair() {}
  Pair(const T& first, const U& second) : first(first), second(second) {}
  Pair(const Pair& pair) : first(pair.first), second(pair.second) {}
  ~Pair() {}
  Pair& operator=(const Pair& pair) {
    this.first = pair.first;
    this.second = pair.second;
    return &*this;
  }
  friend bool operator==(const Pair& left, const Pair& right) {
    return left.first == right.first && left.second == right.second;
  }
  friend bool operator<(const Pair& left, const Pair& right) {
    return left.first < right.first && left.second < right.second;
  }
  friend bool operator>(const Pair& left, const Pair& right) {
    return right > left;
  }
};

int main() {
  Pair pair{1, 2};
  std::cout << pair.first << ", " << pair.second << std::endl;
}
