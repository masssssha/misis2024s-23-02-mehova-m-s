#include <iostream>
#include <vector>
#include <string>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    std::string s;
    std::cin >> s;
    int count_a(0), count_b(0);
    for (int i = 0; i < 5; i++) {
      if (s[i] == 'A') {
        count_a += 1;
      }
      else {
        count_b += 1;
      }
    }
    if (count_a > count_b) {
      std::cout << "A" << std::endl;
    }
    else {
      std::cout << "B" << std::endl;
    }
  }
}
