#include <iostream>
#include <algorithm>

int main() {
  int a[] = { 1, 3, 1, 4, 1, 5 };
  std::sort(a, a + 6);
  std::cout << std::unique(a, a + 6) - a << std::endl;
}
