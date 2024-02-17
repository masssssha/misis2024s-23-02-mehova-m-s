#include <iostream>
#include <vector>
#include <string>

int main()
{
  int n(0);
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<int> a;
  int count_one(0);
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      count_one += 1;
    }
    if (s[i] == '0' || i == n - 1) {
      a.push_back(count_one);
      count_one = 0;
    }
  }
  if (s[n - 1] == '0') {
    a.push_back(0);
  }
  for (int i = 0; i < a.size(); i++) {
    std::cout << a[i];
  }
}