#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void rotateCW(std::vector<std::vector<T>> &grid) {
    int n = grid.size(), m = grid[0].size();
    std::vector<std::vector<T>> ngrid(m, std::vector<T>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ngrid[j][n - i - 1] = grid[i][j];
    grid = ngrid;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> vals;
    std::string s;
    while (getline(std::cin, s))
        vals.emplace_back(s);

    int n = static_cast<int>(vals.size());
    int m = static_cast<int>(vals[0].size());

    int res = 0;

    for (int i = 0; i + 2 < n; i++) {
        for (int j = 0; j + 2 < m; j++) {
            std::vector<std::vector<int>> x(3, std::vector<int>(3));
            for (int dx = 0; dx < 3; dx++)
                for (int dy = 0; dy < 3; dy++)
                    x[dx][dy] = vals[i + dx][j + dy];
            bool ok = false;
            for (int dx = 0; dx < 4; dx++) {
                if (x[0][0] == 'M' && x[0][2] == 'S' && x[1][1] == 'A' &&
                    x[2][0] == 'M' && x[2][2] == 'S') {
                    ok = true;
                }
                rotateCW(x);
            }
            if (ok)
                ++res;
        }
    }

    std::cout << res;

    return 0;
}
