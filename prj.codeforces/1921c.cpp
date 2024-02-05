#include <iostream>
#include <string>
#include <vector>

int main() {
  int t(0);
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    long long n(0), energy(0), a(0), b(0);
    std::cin >> n >> energy >> a >> b;
    long long count(0);
    std::vector<long long> times(n);
    for (int j = 0; j < n; j++) {
      std::cin >> times[j];
    }
    count += std::min(times[0] * a, b);
    for (int j = 1; j < n; j++) {
      count += std::min((times[j] - times[j - 1]) * a, b);
    }
    if (count < energy) {
      std::cout << "YES" << std::endl;
    }
    else {
      std::cout << "NO" << std::endl;
    }
  }
}
