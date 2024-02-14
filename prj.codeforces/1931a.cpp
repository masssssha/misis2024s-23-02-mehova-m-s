#include <iostream>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    int sum(0);
    std::cin >> sum;
    if (sum <= 28) {
      std::cout << "aa" << char('a' + sum - 3) << std::endl;
    }
    if (sum > 28 && sum <= 53) {
      std::cout << 'a' << char('a' + sum - 28) << 'z' << std::endl;
    }
    if (sum > 53) {
      std::cout << char('a' + sum - 53) << "zz" << std::endl;
    }
  }
}
