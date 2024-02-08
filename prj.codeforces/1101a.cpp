#include <iostream>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long l(0), r(0), q(0);
    std::cin >> l >> r >> q;
    if (q < l || q > r) {
      std::cout << q << std::endl;
    }
    else {
      long long ost(r % q);
      std::cout << (r + q - r % q) << std::endl;
    }
  }
}
