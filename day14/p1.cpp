#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::vector<std::vector<std::string>> vals;
    std::string s;

    constexpr int n = 103;
    constexpr int m = 101;

    std::vector<std::vector<int>> grid(n, std::vector<int>(m));

    while (getline(std::cin, s)) {
        int cur = 0;
        std::vector<int> vals;
        bool in = false, neg = false;
        for (auto &str : s) {
            if (str == '-') {
                neg = true;
            } else if (!isdigit(str)) {
                if (in) {
                    if (neg)
                        vals.emplace_back(-cur);
                    else
                        vals.emplace_back(cur);
                }
                cur = 0;
                in = false;
                neg = false;
            } else {
                in = true;
                cur = (cur * 10) + (str - '0');
            }
        }
        if (in) {
            if (neg)
                vals.emplace_back(-cur);
            else
                vals.emplace_back(cur);
        }
        int sx = vals[0], sy = vals[1];
        int dx = vals[2], dy = vals[3];
        std::swap(sx, sy);
        std::swap(dx, dy);
        for (int i = 0; i < 100; i++) {
            sx = (sx + dx) % n, sx += n, sx %= n;
            sy = (sy + dy) % m, sy += m, sy %= m;
        }
        grid[sx][sy]++;
    }

    int first = 0, second = 0, third = 0, fourth = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == n / 2 || j == m / 2)
                continue;
            if (i < n / 2 && j < m / 2)
                first += grid[i][j];
            if (i >= n / 2 && j < m / 2)
                second += grid[i][j];
            if (i >= n / 2 && j > m / 2)
                third += grid[i][j];
            if (i < n / 2 && j > m / 2)
                fourth += grid[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            std::cout << grid[i][j] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << first << ' ' << second << ' ' << third << ' ' << fourth
              << std::endl;
    std::cout << first * second * third * fourth << std::endl;

    return 0;
}