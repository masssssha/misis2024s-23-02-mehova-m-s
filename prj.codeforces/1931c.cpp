#include <iostream>
#include <vector>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long n(0);
    std::cin >> n;
    std::vector<long long> a(n);
    std::vector<int> povt(n, 0);
    int count(0), first(0), last(n-1);
    std::cin >> a[0];
    count = 1;
    povt[first] = 1;
    for (int i = 1; i < n; i++) {
      std::cin >> a[i];
      if (a[i] == a[i-1]) {
        povt[i] = povt[i - 1] + 1;
      }
      else {
        if (count == 1) {
          first = i - 1;
          count = 0;
        }
      }
    }
    if (povt[last] != n) {
      povt[last] += 1;
    }
    if (a[0] == a[last] && povt[last] != n) {
      povt[last] += povt[first];
    }
    std::cout << (n - std::max(povt[first], povt[last])) << std::endl;
  }
}
