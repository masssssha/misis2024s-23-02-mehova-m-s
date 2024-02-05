#include <iostream>
#include <string>

int main() {
  int t(0);
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    int n(0);
    std::cin >> n;
    std::string a;
    std::string b;
    std::string c;
    std::cin >> a >> b >> c;
    int count(0);
    for (int j = 0; j < n; j++) {
      if (c[j] != a[j] && c[j] != b[j]) {
        count += 1;
      }
    }
    if (count != 0) {
      std::cout << "YES" << std::endl;
    }
    else {
      std::cout << "NO" << std::endl;
    }
  }
}
