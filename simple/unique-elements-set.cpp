#include <iostream>
#include <set>
int main() {
  int a[] = { 1, 3, 1, 4, 1, 5 };
  std::set<int> s;
  for (const int item : a) {
    s.insert(item);
  }
  std::cout << s.size() << std::endl;
}
