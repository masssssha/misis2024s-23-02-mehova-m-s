#include <iostream>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  long long l(0), r(0);
  std::cin >> l >> r;
  long long i(l);
  std::cout << "YES" << std::endl;
  while (i <= r) {
    std::cout << i << " " << (i + 1) << std::endl;
    i += 2;
  }
}
