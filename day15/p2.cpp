#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid;
    std::string s;
    std::string cmds;

    bool is_cmd = false;
    while (getline(std::cin, s))
        if (s.empty())
            is_cmd = true;
        else if (is_cmd)
            cmds += s;
        else
            grid.emplace_back(s);

    for (auto &row : grid) {
        std::string nrow;
        for (auto &ch : row) {
            if (ch == '#')
                nrow += "##";
            if (ch == 'O')
                nrow += "[]";
            if (ch == '.')
                nrow += "..";
            if (ch == '@')
                nrow += "@.";
        }
        row = nrow;
    }

    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());

    int x, y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '@')
                x = i, y = j;
    }

    for (auto &cmd : cmds) {
        int dx, dy;
        if (cmd == '^')
            dx = -1, dy = 0;
        else if (cmd == '>')
            dx = 0, dy = 1;
        else if (cmd == '<')
            dx = 0, dy = -1;
        else
            dx = 1, dy = 0;
        bool move = true;

        std::vector<std::pair<int, int>> vec;
        std::queue<std::pair<int, int>> q;
        q.emplace(x, y);
        std::vector<std::vector<bool>> vis(n, std::vector<bool>(m));
        vis[x][y] = true;

        while (!q.empty()) {
            auto [sx, sy] = q.front();
            q.pop();
            vec.emplace_back(sx, sy);
            if (grid[sx][sy] == '@') {
                int nx = sx + dx;
                int ny = sy + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (grid[nx][ny] == '#') {
                        move = false;
                        break;
                    }
                    if (grid[nx][ny] == '[' && !vis[nx][ny]) {
                        vis[nx][ny] = true;
                        q.emplace(nx, ny);
                    }
                    if (grid[nx][ny] == ']' && !vis[nx][ny - 1]) {
                        vis[nx][ny - 1] = true;
                        q.emplace(nx, ny - 1);
                    }
                }
            } else {
                for (auto &[cx, cy] :
                     {std::make_pair(sx, sy), std::make_pair(sx, sy + 1)}) {
                    int nx = cx + dx;
                    int ny = cy + dy;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                        if (grid[nx][ny] == '#') {
                            move = false;
                            break;
                        }
                        if (grid[nx][ny] == '[' && !vis[nx][ny]) {
                            vis[nx][ny] = true;
                            q.emplace(nx, ny);
                        }
                        if (grid[nx][ny] == ']' && !vis[nx][ny - 1]) {
                            vis[nx][ny - 1] = true;
                            q.emplace(nx, ny - 1);
                        }
                    }
                }
            }
        }

        if (move) {
            auto ngrid = grid;

            for (auto &[sx, sy] : vec)
                if (grid[sx][sy] == '[')
                    ngrid[sx][sy] = ngrid[sx][sy + 1] = '.';
                else
                    ngrid[sx][sy] = '.';

            for (auto &[sx, sy] : vec) {
                if (grid[sx][sy] == '[') {
                    ngrid[sx + dx][sy + dy] = '[';
                    ngrid[sx + dx][sy + 1 + dy] = ']';
                } else {
                    ngrid[sx + dx][sy + dy] = '@';
                    x = sx + dx;
                    y = sy + dy;
                }
            }

            grid = ngrid;
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '[')
                res += 100 * i + j;
    }
    std::cout << res << std::endl;

    return 0;
}