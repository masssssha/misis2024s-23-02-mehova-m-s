#include <iostream>
#include <vector>
#include <string>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    int n(0);
    std::cin >> n;
    std::vector<int> count(n);
    int ind(-1);
    for (int i = 0; i < n; i++) {
      int curr(0);
      std::string s;
      std::cin >> s;
      for (int k = 0; k < n; k++) {
        curr += ((int)s[k] - '0');
      }
      count[i] = curr;
      if (curr != 0 && ind == -1) {
        ind = i;
      }
    }
    if (count[ind + 1] == count[ind]) {
      std::cout << "SQUARE" << std::endl;
    }
    else {
      std::cout << "TRIANGLE" << std::endl;
    }
  }
}
