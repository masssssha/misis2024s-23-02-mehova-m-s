#include <iostream>
#include <cmath>
#include <string>
#include <vector>

long long nod(long long a, long long b) {
  while (a && b)
    if (a > b) a %= b;
    else b %= a;
  return a + b;
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
      std::cout << ans << std::endl;
    }
  }
}
