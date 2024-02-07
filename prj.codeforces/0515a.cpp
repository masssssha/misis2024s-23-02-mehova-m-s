#include <iostream>

int main() {
  long long a(0), b(0), s(0);
  std::cin >> a >> b >> s;
  long long sum(std::abs(a) + std::abs(b));
  if ((s - sum) % 2 == 0 && (s - sum) >= 0) {
    std::cout << "Yes";
  }
  else {
    std::cout << "No";
  }
}
