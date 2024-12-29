#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using ll = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid;
    std::string s;
    while (std::getline(std::cin, s))
        grid.emplace_back(s);

    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    int x = -1, y = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == 'S')
                x = i, y = j;
    }

    const int dx[] = {1, 0, -1, 0};
    const int dy[] = {0, 1, 0, -1};

    auto in_bounds = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    std::priority_queue<std::tuple<int, int, int, int>,
                        std::vector<std::tuple<int, int, int, int>>,
                        std::greater<std::tuple<int, int, int, int>>>
        pq;

    const int INF = 1e9;
    std::vector<std::vector<std::vector<int>>> dist(
        n, std::vector<std::vector<int>>(m, std::vector<int>(4, INF)));
    std::vector<std::vector<std::vector<bool>>> vis(
        n, std::vector<std::vector<bool>>(m, std::vector<bool>(4)));

    for (int i = 0; i < 4; ++i) {
        dist[x][y][i] = 1000 * i;
        pq.emplace(dist[x][y][i], x, y, i);
    }

    std::vector<std::vector<std::vector<bool>>> seen(
        n, std::vector<std::vector<bool>>(m, std::vector<bool>(4)));

    std::set<std::pair<int, int>> visited_positions;

    const auto count_paths = [&](auto &&self, int i, int j,
                                 int cur_dir) -> void {
        if (seen[i][j][cur_dir])
            return;
        seen[i][j][cur_dir] = true;
        visited_positions.emplace(i, j);

        int min_cost = INF;
        for (int dir = 0; dir < 4; ++dir) {
            int nx = i + dx[dir];
            int ny = j + dy[dir];
            for (int xdir = 0; xdir < 4; ++xdir) {
                for (int ydir = 0; ydir < 4; ++ydir) {
                    int xx = nx + dx[ydir];
                    int yy = ny + dy[ydir];
                    if (xx == i && yy == j) {
                        int cost = dist[nx][ny][xdir];
                        if (xdir != ydir) {
                            int turns1 = (xdir - ydir + 4) % 4;
                            int turns2 = (ydir - xdir + 4) % 4;
                            cost += std::min(turns1, turns2) * 1000;
                        }
                        if (cost + 1 == dist[i][j][cur_dir])
                            self(self, nx, ny, xdir);
                        min_cost = std::min(min_cost, cost);
                    }
                }
            }
        }
    };

    while (!pq.empty()) {
        auto [score, i, j, cur_dir] = pq.top();
        pq.pop();

        if (vis[i][j][cur_dir])
            continue;

        if (grid[i][j] == 'E') {
            count_paths(count_paths, i, j, cur_dir);
            std::cout << visited_positions.size() << std::endl;
            return 0;
        }

        vis[i][j][cur_dir] = true;

        for (int dir = 0; dir < 4; ++dir) {
            int nx = i + dx[dir];
            int ny = j + dy[dir];
            if (in_bounds(nx, ny) && grid[nx][ny] != '#') {
                int nscore = score + 1;
                if (dir != cur_dir) {
                    int turns1 = (dir - cur_dir + 4) % 4;
                    int turns2 = (cur_dir - dir + 4) % 4;
                    nscore += std::min(turns1, turns2) * 1000;
                }
                if (nscore < dist[nx][ny][dir]) {
                    dist[nx][ny][dir] = nscore;
                    pq.emplace(dist[nx][ny][dir], nx, ny, dir);
                }
            }
        }
    }

    return 0;
}
