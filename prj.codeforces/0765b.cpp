#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string s;
  std::cin >> s;
  std::vector<int> letters(27, 0);
  letters[0] = 1;
  int flag(0);
  for (int i = 0; i < s.length(); i++) {
    if (letters[(int)s[i] - 'a'] == 0) {
      flag = 1;
      break;
    }
    letters[(int)s[i] - 'a' + 1] = 1;
    std::cout << i << " " << s[i] << std::endl;
  }
  if (flag == 0) {
    std::cout << "YES";
  }
  else {
    std::cout << "NO";
  }
}