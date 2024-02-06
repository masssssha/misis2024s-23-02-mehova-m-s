#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    int n(0), k(0), x(0);
    std::cin >> n >> k >> x;
    std::vector<int> a(n);
    long long sum(0), sum_max(0);
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
      sum += a[i];
    }
    std::sort(a.begin(), a.end());
    std::reverse(a.begin(), a.end());
    for (int i = 0; i < x; i++) {
      sum_max += a[i];
    }
    long long ans(-20000000000), ind(0);
    ans = std::max(ans, sum - 2 * sum_max);
    while (k > 0) {
      sum -= a[ind];
      sum_max -= a[ind];
      if (x + ind < n) {
         sum_max += a[x + ind];
      }
      ans = std::max(ans, sum - 2 * sum_max);
      ind += 1;
      k -= 1;
    }
    std::cout << ans << std::endl;
  }
}
