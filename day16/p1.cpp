#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using ll = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid;
    std::string s;
    while (std::getline(std::cin, s))
        grid.emplace_back(s);

    int n = (int) grid.size();
    int m = (int) grid[0].size();
    int x = -1, y = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }

    const int dx[] = {1, 0, -1, 0};
    const int dy[] = {0, 1, 0, -1};

    auto in = [&](int x, int y) {
        return (x >= 0 && x < n && y >= 0 && y < m);
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

    for (int i = 0; i < 4; i++) {
        dist[x][y][i] = 1000 * i;
        pq.emplace(dist[x][y][i], x, y, i);
    }

    while (!pq.empty()) {
        auto [score, i, j, cur_dir] = pq.top();
        pq.pop();

        if (vis[i][j][cur_dir])
            continue;

        if (grid[i][j] == 'E') {
            std::cout << dist[i][j][cur_dir] - 1000 << std::endl;
            exit(0);
        }

        vis[i][j][cur_dir] = true;

        for (int dir = 0; dir < 4; dir++) {
            int nx = i + dx[dir];
            int ny = j + dy[dir];

            if (in(nx, ny) && grid[nx][ny] != '#') {
                int nscore = score + 1;

                if (dir != cur_dir) {
                    int turns1 = dir - cur_dir;
                    turns1 += 4;
                    turns1 %= 4;
                    int turns2 = cur_dir - dir;
                    turns2 += 4;
                    turns2 %= 4;
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
