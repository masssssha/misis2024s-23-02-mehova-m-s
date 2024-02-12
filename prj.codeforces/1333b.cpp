#include <iostream>
#include <vector>

int main() {
    int t(0);
    std::cin >> t;
    for (int j = 0; j < t; j++) {
        int n(0);
        std::cin >> n;
        std::vector<int> a(n);
        std::vector<long long> b(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> b[i];
        }
        int count_ones(0), count_min(0);
        if (a[0] != b[0]) {
            std::cout << "NO" << std::endl;
        }
        else {
            if (a[0] == 1) {
                count_ones += 1;
            }
            if (a[0] == -1) {
                count_min += 1;
            }
            int flag(0);
            for (int i = 1; i < n; i++) {
                if (a[i] > b[i] && count_min == 0) {
                    flag = 1;
                    break;
                }
                if (a[i] < b[i] && count_ones == 0) {
                    flag = 1;
                    break;
                }
                if (a[i] == 1) {
                    count_ones += 1;
                }
                if (a[i] == -1) {
                    count_min += 1;
                }
            }
            if (flag == 1) {
                std::cout << "NO" << std::endl;
            }
            else {
                std::cout << "YES" << std::endl;
            }
        }
    }
}
