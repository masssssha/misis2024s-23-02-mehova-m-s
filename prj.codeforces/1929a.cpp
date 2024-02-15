#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    int n(0);
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    long long sum(0);
    for (int i = 1; i < n; i++) {
      sum = sum + (a[i] - a[i - 1]);
    }
    std::cout << sum << std::endl;
  }
}
