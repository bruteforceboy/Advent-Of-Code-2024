#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

using ll = long long;

auto split(std::string str, char delim) -> std::vector<std::string> {
    std::vector<std::string> res;
    std::string buffer;

    for (auto &ch : str) {
        if (ch == delim) {
            if (!buffer.empty())
                res.push_back(buffer);
            buffer.clear();
        } else {
            buffer += ch;
        }
    }

    if (!buffer.empty())
        res.push_back(buffer);
    return res;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::vector<std::pair<ll, ll>> pts;
    std::string s;

    while (std::getline(std::cin, s)) {
        auto cur = split(s, ',');
        pts.emplace_back(std::stoll(cur[1]), std::stoll(cur[0]));
    }

    ll n = 0, m = 0;
    for (int i = 0; i < (int) pts.size(); i++) {
        n = std::max(n, pts[i].first + 1);
        m = std::max(m, pts[i].second + 1);
    }
    std::cout << "n: " << n << " m: " << m << std::endl;

    auto can = [&](int cnt) -> bool {
        std::vector<std::vector<int>> grid(n, std::vector<int>(m, -1));
        for (int i = 0; i < cnt; i++) {
            grid[pts[i].first][pts[i].second] = 1;
            std::cout << pts[i].first << ' ' << pts[i].second << std::endl;
        }

        std::vector<std::vector<int>> dist(n, std::vector<int>(m));
        std::vector<std::vector<bool>> vis(n, std::vector<bool>(m, false));
        std::queue<std::pair<int, int>> q;

        if (grid[0][0] != 1) {
            q.emplace(0, 0);
            vis[0][0] = true;
            dist[0][0] = 0;
        }

        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};

        auto in = [&](int x, int y) {
            return (x >= 0 && x < n && y >= 0 && y < m);
        };

        while (!q.empty()) {
            auto [sx, sy] = q.front();
            q.pop();

            for (int dir = 0; dir < 4; dir++) {
                int nx = sx + dx[dir];
                int ny = sy + dy[dir];
                if (in(nx, ny) && !vis[nx][ny] && grid[nx][ny] != 1) {
                    vis[nx][ny] = true;
                    dist[nx][ny] = dist[sx][sy] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        return vis[n - 1][m - 1];
    };

    ll lo = 1, hi = (int) pts.size(), ans = 0;

    while (lo <= hi) {
        ll mid = lo + hi >> 1;
        if (!can(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    std::cout << pts[ans - 1].second << "," << pts[ans - 1].first << std::endl;
    return 0;
}