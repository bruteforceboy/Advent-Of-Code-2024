#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> vals;
    std::string s;

    while (getline(std::cin, s))
        vals.emplace_back(s);

    int n = static_cast<int>(vals.size());
    int m = static_cast<int>(vals[0].size());

    int res = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
            const int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};
            auto in = [&](int x, int y) {
                return (x >= 0 && x < n && y >= 0 && y < m);
            };
            for (int dir = 0; dir < 8; dir++) {
                int x = i, y = j;
                std::string cur;
                cur += vals[i][j];
                for (int k = 0; k < 4; k++) {
                    x += dx[dir];
                    y += dy[dir];
                    if (in(x, y)) {
                        cur += vals[x][y];
                        if (cur == "XMAS")
                            ++res;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    std::cout << res;

    return 0;
}
