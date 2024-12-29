#include <algorithm>
#include <iostream>
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
        int nx = x, ny = y;
        while (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '@' ||
               grid[nx][ny] == 'O') {
            nx += dx;
            ny += dy;
        }
        if (grid[nx][ny] == '.') {
            while (!(nx == x && ny == y)) {
                std::swap(grid[nx][ny], grid[nx - dx][ny - dy]);
                nx -= dx;
                ny -= dy;
            }
            x += dx, y += dy;
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 'O')
                res += 100 * i + j;
    }

    std::cout << res << '\n';

    return 0;
}