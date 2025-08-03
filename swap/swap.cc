#include <iostream>
template
<typename T>
void swap(T& left, T& right) {
  T temporary(left);
  left = right;
  right = temporary;
}
int main() {
  int s(1), t(2);
  swap(s, t);
  std::cout << s << " " << t << std::endl;
}
