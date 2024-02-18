#include <iostream>
#include <vector>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long n(0);
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
      if (i != 0 && a[i] <= a[i - 1]) {
        long long temp(a[i]);
        while (a[i] <= a[i - 1]) {
          a[i] += temp;
        }
      }
    }
    std::cout << a[n - 1] << std::endl;
  }
}
