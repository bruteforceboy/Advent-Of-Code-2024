#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid;
    std::string s;
    while (getline(std::cin, s))
        grid.emplace_back(s);

    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());

    std::vector vis(n, std::vector<bool>(m));

    int area = 0, perim = 0, sz = std::max(n, m);

    std::vector<std::vector<std::set<int>>> vals(
        4, std::vector<std::set<int>>(sz));

    const auto dfs = [&](auto &&self, int i, int j) -> void {
        ++area;
        vis[i][j] = true;
        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};

        auto in = [&](int x, int y) {
            return (x >= 0 && x < n && y >= 0 && y < m);
        };
        for (int dir = 0; dir < 4; dir++) {
            int nx = i + dx[dir];
            int ny = j + dy[dir];
            if (!in(nx, ny) || grid[nx][ny] != grid[i][j]) {
                if (dx[dir] != 0)
                    vals[dir][i].emplace(ny);
                else
                    vals[dir][j].emplace(nx);
            }
        }
        for (int dir = 0; dir < 4; dir++) {
            int nx = i + dx[dir];
            int ny = j + dy[dir];
            if (in(nx, ny) && !vis[nx][ny] && grid[nx][ny] == grid[i][j])
                self(self, nx, ny);
        }
    };

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j]) {
                for (int dir = 0; dir < 4; dir++)
                    for (int i = 0; i < sz; i++)
                        vals[dir][i].clear();
                area = 0, perim = 0;
                dfs(dfs, i, j);
                for (int dir = 0; dir < 4; dir++) {
                    for (int i = 0; i < sz; i++) {
                        std::vector<int> cur(begin(vals[dir][i]),
                                             end(vals[dir][i]));
                        if (!cur.empty()) {
                            ++perim;
                            for (int i = 1; i < (int) cur.size(); i++)
                                if (cur[i] != cur[i - 1] + 1)
                                    ++perim;
                        }
                    }
                }

                res += area * perim;
            }
        }
    }

    std::cout << res << '\n';
    return 0;
}