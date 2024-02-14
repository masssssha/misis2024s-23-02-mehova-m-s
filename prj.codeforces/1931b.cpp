#include <iostream>
#include <vector>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long n(0), sum(0);
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
      sum += a[i];
    }
    if (a[0] < sum / n || a[n - 1] > sum / n) {
      std::cout << "NO" << std::endl;
    }
    else {
      long long prev_sum(a[0] - sum/n), flag(0);
      for (int i = 1; i < n; i++) {
        if (a[i] < sum / n) {
          if ((sum / n - a[i]) > prev_sum) {
            flag = 1;
            break;
          }
          else {
            prev_sum -= (sum / n - a[i]);
          }
        }
        else {
          prev_sum += (a[i] - sum / n);
        }
      }
      if (prev_sum == 0 && flag == 0) {
        std::cout << "YES" << std::endl;
      }
      else {
        std::cout << "NO" << std::endl;
      }
    }
  }
}
