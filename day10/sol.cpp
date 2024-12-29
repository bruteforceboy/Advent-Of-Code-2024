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

    int ret = 0;

    std::vector<std::vector<bool>> vis(n, std::vector<bool>(m));
    const auto dfs = [&](auto &self, int i, int j) -> void {
        if (vals[i][j] == '9' && !vis[i][j])
            ++ret;

        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};

        auto in = [&](int x, int y) {
            return (x >= 0 && x < n && y >= 0 && y < m);
        };

        for (int dir = 0; dir < 4; dir++) {
            int nx = i + dx[dir];
            int ny = j + dy[dir];
            if (in(nx, ny) && vals[nx][ny] != '.' &&
                vals[nx][ny] - vals[i][j] == 1) {
                self(self, nx, ny);
            }
        }
    };

    int cnt9 = 0;
    for (int i = 0; i < n; i++)
        cnt9 += count(begin(vals[i]), end(vals[i]), '9');

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vals[i][j] == '0') {
                ret = 0;
                vis = std::vector<std::vector<bool>>(n, std::vector<bool>(m));
                dfs(dfs, i, j);
                res += ret;
            }
        }
    }

    std::cout << res << '\n';
    return 0;
}