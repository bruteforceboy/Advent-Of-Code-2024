#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

constexpr int PICO_SECONDS =
#ifdef P1
    2
#else
    20
#endif
    ;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::vector<std::string> grid;
    std::string s;

    while (std::getline(std::cin, s))
        grid.emplace_back(s);

    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    int sx, sy, ex, ey;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            }
            if (grid[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }

    const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
    const int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};
    auto in = [&](int x, int y) {
        return (x >= 0 && x < n && y >= 0 && y < m);
    };

    const int INF = 1e9;
    const auto get_dists = [&](int x, int y, std::vector<std::string> &ngrid) {
        std::vector<std::vector<bool>> vis(n, std::vector<bool>(m));
        std::vector<std::vector<int>> dist(n, std::vector<int>(m, INF));
        std::queue<std::pair<int, int>> q;
        q.emplace(x, y);
        vis[x][y] = true;
        dist[x][y] = 0;
        while (!q.empty()) {
            auto [sx, sy] = q.front();
            q.pop();
            for (int dir = 0; dir < 4; dir++) {
                int nx = sx + dx[dir];
                int ny = sy + dy[dir];
                if (in(nx, ny) && !vis[nx][ny] && ngrid[nx][ny] != '#') {
                    vis[nx][ny] = true;
                    dist[nx][ny] = dist[sx][sy] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        return dist;
    };

    auto dist1 = get_dists(sx, sy, grid);
    auto dist2 = get_dists(ex, ey, grid);

    int actual_time = dist1[ex][ey];
    std::map<int, int> mp;
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (grid[i][j] != '#') {
                std::vector<std::pair<int, int>> to;
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < m; y++)
                        if (std::abs(x - i) + std::abs(y - j) <= PICO_SECONDS &&
                            grid[x][y] != '#')
                            to.emplace_back(x, y);
                }
                for (auto &[x, y] : to) {
                    int cur_time = dist1[i][j] + std::abs(x - i) +
                                   std::abs(y - j) + dist2[x][y];
                    if (actual_time - cur_time >= 100)
                        ++res;
                    if (cur_time < actual_time)
                        mp[actual_time - cur_time]++;
                }
            }
    }

    for (auto &[x, y] : mp)
        std::cout << "x: " << x << " y: " << y << std::endl;
    std::cout << std::endl;

    std::cout << res << '\n';
    return 0;
}