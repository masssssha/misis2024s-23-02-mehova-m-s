#include <iostream>
#include <vector>
#include <string>

int main() {
  int t(0);
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    int n(0);
    std::cin >> n;
    std::vector<int> free;
    int count_ones(0);
    int count_temps(0);
    std::vector <int> temps(n, 0);
    std::vector <int> ones;
    std::vector <int> all(n);
    int flag(0);
    int ind_first_last(-1);
    for (int j = 0; j < n; j++) {
      int temp(0);
      std::cin >> temp;
      if (temp == 1) {
        count_ones += 1;
        count_temps += 1;
        ones.push_back(j);
      }
      else {
        if (ind_first_last == -1 && count_ones != 0) {
          ind_first_last = j-1;
        }
        count_temps = 0;
      }
      temps[j] = count_temps;
      all[j] = temp;
    }
    if (ind_first_last == -1 || temps[ind_first_last] == count_ones) {
      std::cout << "0" << std::endl;
    }
    else {
      int ans(0);
      for (int j = ones[ones.size() - 1]; j > ind_first_last; j--) {
        if (all[j] == 1) {
          if (all[j - 1] == 0) {
            ans += 1;
            all[j - 1] = 1;
            all[j] = 0;
          }
          else {
            int k(j);
            while (all[k] != 0 && k != ind_first_last) {
              k -= 1;
            }
            if (k == ind_first_last) {
              break;
            }
            all[k] = 1;
            all[j] = 0;
            ans += 1;
          }
        }
      }
      std::cout << ans << std::endl;
    }
  }
}
