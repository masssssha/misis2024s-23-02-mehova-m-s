#include <iostream>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    long long n(0);
    std::cin >> n;
    long long chet(0), nechet(1);
    if (n % 2 == 0) {
      chet = n;
      for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
          std::cout << chet << " ";
          chet -= 2;
        }
        else {
          std::cout << nechet << " ";
          nechet += 2;
        }
      }
    }
    else {
      chet = n - 1;
      for (int i = 0; i < n; i++) {
        if (i % 2 != 0) {
          std::cout << chet << " ";
          chet -= 2;
        }
        else {
          std::cout << nechet << " ";
          nechet += 2;
        }
      }
    }
    std::cout << std::endl;
  }
}
