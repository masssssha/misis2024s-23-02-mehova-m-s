#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  long long t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long n(0);
    std::cin >> n;
    n *= 2;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    long long sum(0);
    long long i(1);
    while (i < n) {
      sum += std::min(a[i - 1], a[i]);
      i += 2;
    }
    std::cout << sum << std::endl;
  }
}
