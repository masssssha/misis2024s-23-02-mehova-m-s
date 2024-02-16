#include <iostream>
#include <vector>
#include <string>

int main()
{
  long long k(0);
  std::cin >> k;
  std::string s;
  std::cin >> s;
  long long sum(0);
  std::vector<long long> count(10, 0);
  for (int i = 0; i < s.length(); i++) {
    count[(int)s[i] - '0'] += 1;
    sum += ((int)s[i] - '0');
  }
  if (sum < k) {
    int need(k - sum), ans(0);
    for (int i = 0; i < 10; i++) {
      if (need > 0) {
        if (need - (count[i] * (9 - i)) < 0) {
          while (count[i] != 0 && need > 0) {
            ans += 1;
            count[i] -= 1;
            need -= (9 - i);
          }
        }
        else {
          ans += count[i];
          need -= (count[i] * (9 - i));
        }
      }
      else {
        break;
      }
    }
    std::cout << ans;
  }
  else {
    std::cout << "0";
  }
}