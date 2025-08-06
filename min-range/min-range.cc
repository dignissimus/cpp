#include <iostream>
#include <format>
#include <functional>
#include <concepts>
#include <utility>

template
<typename I, typename Compare>
I min_element(I begin, I end, Compare compare){
  if (begin == end) {
    return end;
  }
  I result = begin;
  while (begin != end) {
    if (compare(*begin, *result)) {
      result = begin;
    }
    ++begin;
  }
  return result;
}

template
<typename I, typename Compare>
std::pair<I, I> minmax_element1(I begin, I end, Compare compare) {
  I min = begin;
  I max = begin;
  while (begin != end) {
    if (compare(*max, *begin)) {
      max = begin;
    }
    else if (compare(*begin, *min)) {
      min = begin;
    }
    ++begin;
  }
  return std::make_pair(min, max);
}

template
<typename I, typename Compare>
std::pair<I, I> minmax_element(I begin, I end, Compare compare) {
  I min = begin;
  I max = begin;
  if (begin == end) {
    return std::make_pair(end, end);
  }
  while (begin != end) {
    I potential_minimum = begin++;
    if (begin == end) {
      break;
    }
    I potential_maximum = begin++;
    if (compare(*potential_maximum, *potential_minimum)) {
      std::swap(potential_maximum, potential_minimum);
    }
    if (compare(*potential_minimum, *min)) {
      min = potential_minimum;
    }
    if (compare(*max, *potential_maximum)) {
      max = potential_maximum;
    }
  }
  return std::make_pair(min, max);
}

int main() {
  std::vector<int> v{4, 3, 2, 1};
  auto me = ::min_element(v.begin(), v.end(), std::less<int>{});
  std::cout << std::format("Minimum element: {}", *me) << std::endl;
  auto [mine, maxe] = ::minmax_element1(v.begin(), v.end(), std::less<int>{});
  std::cout << std::format("Minimum element: {}, Maximum element: {}", *mine, *maxe) << std::endl;
  auto [mine2, maxe2] = ::minmax_element(v.begin(), v.end(), std::less<int>{});
  std::cout << std::format("Minimum element: {}, Maximum element: {}", *mine2, *maxe2) << std::endl;
}
