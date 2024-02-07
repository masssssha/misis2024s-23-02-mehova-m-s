#include <iostream>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long for_y(0), for_x(0);
    std::cin >> for_y >> for_x;
    long long x(0), y(0);
    for (int i = 0; i < 2; i++) {
      int n(0);
      std::cin >> n;
      long long x1(0), x2(0);
      std::cin >> x1;
      for (int l = 1; l < n; l++) {
        std::cin >> x2;
      }
      x = std::max(x, x2 - x1);
    }
    for (int i = 0; i < 2; i++) {
      int n(0);
      std::cin >> n;
      long long x1(0), x2(0);
      std::cin >> x1;
      for (int l = 1; l < n; l++) {
        std::cin >> x2;
      }
      y = std::max(y, x2 - x1);
    }
    std::cout << std::max(x * for_x, y * for_y) << std::endl;
  }
}
