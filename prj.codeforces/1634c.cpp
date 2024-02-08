#include <iostream>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    int n(0), k(0);
    std::cin >> n >> k;
    if (k == 1) {
      std::cout << "YES" << std::endl;
      for (int i = 0; i < n; i++) {
        std::cout << i + 1 << std::endl;
      }
    }
    else if ((n * k) % 2 == 0 && ((n * k) / 2) % k == 0) {
      std::cout << "YES" << std::endl;
      for (int i = 1; i <= n; i++) {
        int count(i);
        for (int j = 0; j < k; j++) {
          std::cout << count << " ";
          count += n;
        }
        std::cout << std::endl;
      }
    }
    else {
      std::cout << "NO" << std::endl;
    }
  }
}
