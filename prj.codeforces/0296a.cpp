#include <iostream>
#include <vector>

int main() {
    int n(0);
    std::cin >> n;
    std::vector<int> a(1001);
    int flag(0);
    for (int i = 0; i < n; i++) {
        int temp(0);
        std::cin >> temp;
        a[temp] += 1;
        if (n % 2 == 0 && a[temp] > n/2) {
            flag = 1;
        }
        if (n%2 != 0 && a[temp] > n/2 + 1) {
            flag = 1;
        }
    }
    if (flag == 0) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
}
