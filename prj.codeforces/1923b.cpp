#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
  int t(0);
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    int n(0), k(0);
    std::cin >> n >> k;
    std::vector<std::vector<int>> a(n, std::vector<int>(2));
    for (int j = 0; j < n; j++) {
      std::cin >> a[j][1];
    }
    for (int j = 0; j < n; j++) {
      int temp(0);
      std::cin >> temp;
      a[j][0] = std::abs(temp);
    }
    std::sort(a.begin(), a.end());
    int s = 0;
    int time(0);
    int flag(0);
    int sum(0);
    while (s < n) {
      if (a[s][0] - time > 0) {
        if (sum + a[s][1] <= k) {
          sum += a[s][1];
        }
        else {
          a[s][1] -= (k - sum);
          sum += (k - sum);
          s--;
        }
        if (sum == k) {
          time += 1;
          sum = 0;
        }
      }
      else {
        flag = 1;
        break;
      }
      s += 1;
    }
    if (flag == 1) {
      std::cout << "NO" << std::endl;
    }
    else {
      std::cout << "YES" << std::endl;
    }
  }
}
