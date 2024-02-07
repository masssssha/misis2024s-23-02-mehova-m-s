#include <iostream>
#include <vector>

int main() {
  int t(0);
  std::cin >> t;
  for (int j = 0; j < t; j++) {
    int k(0);
    std::cin >> k;
    int count(0), ans(0);
    std::vector<int> numbers(10);
    for (int i = 0; i < k; i++) {
      char temp(0);
      std::cin >> temp;
      temp = (int)temp - '0';
      numbers[temp] += 1;
      if (temp == 1 || temp == 4 || temp == 6 || temp == 8 || temp == 9) {
        count = 1;
        ans = temp;
      }
      if (count == 0 && numbers[temp] == 2) {
        count = 2;
        ans = temp * 11;
      }
      if (count == 0) {
        if (temp == 2) {
          if (numbers[3] > 0) {
            count = 2;
            ans = 32;
          }
          else if (numbers[5] > 0) {
            count = 2;
            ans = 52;
          }
          else if (numbers[7] > 0) {
            count = 2;
            ans = 72;
          }
        }
        if (temp == 5) {
          if (numbers[2] > 0) {
            ans = 25;
            count = 2;
          }
          else if (numbers[7] > 0) {
            ans = 75;
            count = 2;
          }
          else if (numbers[3] > 0) {
            ans = 35;
            count = 2;
          }
        }
        if (temp == 7) {
          if (numbers[2] > 0) {
            ans = 27;
            count = 2;
          }
          else if (numbers[5] > 0) {
            ans = 57;
            count = 2;
          }
        }
      }
    }
    std::cout << count << std::endl << ans << std::endl;
  }
}
