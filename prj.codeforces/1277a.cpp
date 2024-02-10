#include <iostream>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long n(0);
    std::cin >> n;
    int colvo(0), zap(0), ones(0);
    long long res(n);
    while (res > 0) {
      colvo += 1;
      if (res % 100 == res % 10) {
        zap = res % 10;
      }
      ones = ones * 10 + 1;
      res /= 10;
    }
    int ans((colvo-1) * 9);
    if (zap * ones <= n) {
      ans += zap;
    }
    else {
      ans += (zap - 1);
    }
    std::cout << ans << std::endl;
  }
}
