#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid;
    std::string s;
    while (getline(std::cin, s))
        grid.emplace_back(s);

    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());

    std::vector has(n, std::vector<int>(m));

    auto ngrid = grid;
    auto add_pt = [&](int x, int y) {
        if (x >= 0 && x < n && y >= 0 && y < m)
            has[x][y] = true;
    };

    std::vector also(n, std::vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = i + 1; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    if (!(x == i && y == j) && grid[i][j] == grid[x][y] &&
                        grid[i][j] != '.') {
                        also[i][j] = also[x][y] = 1;
                        auto dx = x - i;
                        auto dy = y - j;
                        for (int itr = 1; itr <= n; itr++) {
                            add_pt(i - itr * dx, j - itr * dy);
                            add_pt(x + itr * dx, y + itr * dy);
                        }
                    }
                }
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << has[i][j];
            res += has[i][j] || also[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << res << '\n';

    return 0;
}