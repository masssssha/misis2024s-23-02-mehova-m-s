#include <iostream>
#include <cmath>
#include <vector>

long long nod(long long a, long long b) {
  while (a && b)
    if (a > b) a %= b;
    else b %= a;
  return a + b;
}

long long del(long long& c) {
  for (int i = 2; i < (int)std::sqrt(c) + 1; i++) {
    if (c % i == 0) {
      return i;
    }
  }
  return c;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int t(0);
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    long long a(0), b(0);
    std::cin >> a >> b;
    if (b % a == 0) {
      std::cout << b * (b/a) << std::endl;
    }
    else {
      int ans(a * b / nod(a, b));
      if (ans == b) {
        long long ad(del(a));
        long long bd(del(b));
        if (ad == 1) {
          ans *= bd;
        }
        else {
          ans *= std::min(ad, bd);
        }
      }
      std::cout << ans << std::endl;
    }
  }
}
