#include <vector>
#include <utility>
#include <algorithm>


struct InstrumentedBase {
  inline static int copy_constructor_count{};
  inline static int constructor_count{};
  inline static int move_constructor_count{};
  inline static int destructor_count{};
  inline static int copy_assignment_count{};
  inline static int move_assignment_count{};

};

template
<typename T>
struct Instrumented : InstrumentedBase {
  T value;
  Instrumented(const T& value) : value(value) {
    ++constructor_count;
  }
  ~Instrumented() {
    ++destructor_count;
  }
  Instrumented(const Instrumented<T> &other) : value(other.value) {
    ++copy_constructor_count;
  }
  Instrumented(const Instrumented<T> &&other)  noexcept(std::is_nothrow_move_assignable_v<T>) : value(std::move(other.value)) {
    ++move_constructor_count;
  }
  Instrumented<T>& operator=(const Instrumented<T>& other) {
    ++copy_assignment_count;
    value = other.value;
    return &*this;
  }
  Instrumented<T>& operator=(Instrumented<T>&& other) noexcept(std::is_nothrow_move_assignable_v<T>) {
    if (this != &other) {
      value = std::move(other.value);
      ++move_assignment_count;
    }
    return &*this;
  }
};

int main() {
  std::vector<Instrumented<int>> v{1, 2, 3, 4};
}
