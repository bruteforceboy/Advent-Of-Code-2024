#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid;
    std::string s;

    std::vector<std::vector<int>> keys;

    std::string type;
    std::basic_string<bool> kind;

    const auto eval = [&]() {
        int n = (int) grid.size();
        int m = (int) grid[0].size();
        std::vector<int> key;
        if (std::count(begin(grid[0]), end(grid[0]), '#') == m &&
            std::count(begin(grid.back()), end(grid.back()), '.') == m) {
            for (int i = 0; i < m; i++) {
                int cur = 0;
                for (int r = 0; r < n; r++) {
                    if (grid[r][i] == '.')
                        break;
                    ++cur;
                }
                key.emplace_back(cur - 1);
                assert((cur - 1) != -1);
            }
            kind += true;
        } else {
            for (int i = 0; i < m; i++) {
                int cur = 0;
                for (int r = n - 1; r >= 0; r--) {
                    if (grid[r][i] == '.')
                        break;
                    ++cur;
                }
                key.emplace_back(cur - 1);
                assert((cur - 1) != -1);
            }
            kind += false;
        }
        keys.emplace_back(key);
    };

    while (getline(std::cin, s)) {
        grid.emplace_back(s);
        if (s.empty()) {
            grid.pop_back();
            eval();
            grid.clear();
        }
    }
    eval();

    int sz = static_cast<int>(keys.size());
    int res = 0;
    for (int i = 0; i < sz; i++) {
        if (kind[i]) {
            for (int j = 0; j < sz; j++)
                if (!kind[j]) {
                    bool ok = true;
                    int s1 = 0, s2 = 0;
                    for (int x = 0; x < static_cast<int>(keys[i].size()); x++)
                        if (keys[i][x] + keys[j][x] > 5)
                            ok = false;
                    if (ok)
                        res += ok;
                }
        }
    }

    std::cout << res << '\n';

    return 0;
}