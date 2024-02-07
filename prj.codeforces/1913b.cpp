#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    std::string s;
    std::cin >> s;
    int zero(0), one(0);
    std::string ans;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '0') {
        zero += 1;
        ans += '1';
      }
      else {
        one += 1;
        ans += '0';
      }
    }
    if (zero == one) {
      std::cout << "0" << std::endl;
    }
    else {
      int count(0), m(s.length());
      while (zero != one) {
        if (ans[m - 1] == '1' && zero > one) {
          ans[m - 1] = '.';
          zero -= 1;
        }
        if (ans[m - 1] == '0' && zero < one) {
          ans[m - 1] = '.';
          one -= 1;
        }
        m -= 1;
      }
      std::cout << s.length() - m << std::endl;
    }
  }
}
