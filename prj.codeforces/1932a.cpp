#include <iostream>
#include <string>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long n(0);
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long long ans(0);
    for (int i = 0; i < n; i++) {
      if (s[i] == '@') {
        ans += 1;
      }
      if (s[i] == '*' && s[i-1] == '*') {
        break;
      }
    }
    std::cout << ans << std::endl;
  }
}
