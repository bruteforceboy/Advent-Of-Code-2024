#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

// cancer🙏

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid = {"789", "456", "123", "#0A"};
    std::vector<std::string> grid2 = {"0^A", "<v>"};
    std::string code;

    const auto get_pos =
        [&](char ch,
            const std::vector<std::string> &grid) -> std::pair<int, int> {
        for (int i = 0; i < (int) grid.size(); i++) {
            for (int j = 0; j < (int) grid[0].size(); j++)
                if (grid[i][j] == ch)
                    return {i, j};
        }
        assert(false);
        return {-1, -1};
    };

    while (std::getline(std::cin, code)) {
        int x = 3, y = 2;
        std::vector<std::string> ans;

        for (auto &ch : code) {
            auto [tx, ty] = get_pos(ch, grid);
            std::vector<std::string> ways;
            std::string cur;

            const auto get_ways = [&](auto &&self, int x, int y, int tx,
                                      int ty) -> void {
                if (grid[x][y] == '#')
                    return;
                if (x == tx && y == ty) {
                    cur += "A";
                    ways.push_back(cur);
                    cur.pop_back();
                    return;
                }
                if (x < tx) {
                    cur += "v";
                    self(self, x + 1, y, tx, ty);
                    cur.pop_back();
                }
                if (x > tx) {
                    cur += "^";
                    self(self, x - 1, y, tx, ty);
                    cur.pop_back();
                }
                if (y < ty) {
                    cur += ">";
                    self(self, x, y + 1, tx, ty);
                    cur.pop_back();
                }
                if (y > ty) {
                    cur += "<";
                    self(self, x, y - 1, tx, ty);
                    cur.pop_back();
                }
            };

            get_ways(get_ways, x, y, tx, ty);
            x = tx;
            y = ty;

            if (ans.empty()) {
                ans = ways;
            } else {
                std::vector<std::string> nans;
                for (auto &str1 : ans)
                    for (auto &str2 : ways)
                        nans.emplace_back(str1 + str2);
                ans = nans;
            }
        }

        int mn = std::numeric_limits<int>::max();

        for (auto &str : ans) {
            auto solve = [&](std::string str) -> std::vector<std::string> {
                std::vector<std::string> ans;
                int x = 0, y = 2;

                for (auto &ch : str) {
                    auto [tx, ty] = get_pos(ch, grid2);
                    std::vector<std::string> ways;
                    std::string cur;

                    const auto get_ways = [&](auto &&self, int x, int y, int tx,
                                              int ty) -> void {
                        if (grid[x][y] == 'O')
                            return;
                        if (x == tx && y == ty) {
                            cur += "A";
                            ways.push_back(cur);
                            cur.pop_back();
                            return;
                        }
                        if (x < tx) {
                            cur += "v";
                            self(self, x + 1, y, tx, ty);
                            cur.pop_back();
                        }
                        if (x > tx) {
                            cur += "^";
                            self(self, x - 1, y, tx, ty);
                            cur.pop_back();
                        }
                        if (y < ty) {
                            cur += ">";
                            self(self, x, y + 1, tx, ty);
                            cur.pop_back();
                        }
                        if (y > ty) {
                            cur += "<";
                            self(self, x, y - 1, tx, ty);
                            cur.pop_back();
                        }
                    };

                    get_ways(get_ways, x, y, tx, ty);
                    x = tx;
                    y = ty;

                    if (ans.empty()) {
                        ans = ways;
                    } else {
                        std::vector<std::string> nans;
                        for (auto &str1 : ans)
                            for (auto &str2 : ways)
                                nans.emplace_back(str1 + str2);
                        ans = nans;
                    }
                }
                return ans;
            };

            auto solve_one = [&](std::string str) -> std::string {
                std::string res;
                int x = 0, y = 2;

                for (auto &ch : str) {
                    auto [tx, ty] = get_pos(ch, grid2);
                    std::vector<std::string> ways;
                    std::string cur;

                    const auto get_ways = [&](auto &&self, int x, int y, int tx,
                                              int ty) -> void {
                        if (grid[x][y] == 'O')
                            return;
                        if (x == tx && y == ty) {
                            cur += "A";
                            ways.push_back(cur);
                            cur.pop_back();
                            return;
                        }
                        if (x < tx) {
                            cur += "v";
                            self(self, x + 1, y, tx, ty);
                            cur.pop_back();
                        }
                        if (x > tx) {
                            cur += "^";
                            self(self, x - 1, y, tx, ty);
                            cur.pop_back();
                        }
                        if (y < ty) {
                            cur += ">";
                            self(self, x, y + 1, tx, ty);
                            cur.pop_back();
                        }
                        if (y > ty) {
                            cur += "<";
                            self(self, x, y - 1, tx, ty);
                            cur.pop_back();
                        }
                    };

                    get_ways(get_ways, x, y, tx, ty);
                    x = tx;
                    y = ty;
                    res += ways[0];
                }
                return res;
            };

            auto cnt_solve = [&](std::string str) -> int {
                int ret = 0;
                int x = 0, y = 2;

                for (auto &ch : str) {
                    auto [tx, ty] = get_pos(ch, grid2);
                    ret += abs(tx - x) + abs(ty - y) + 1;
                    x = tx;
                    y = ty;
                }
                return ret;
            };

            for (auto &str2 : solve(str)) {
                std::string ans2 = solve_one(str2);
                mn = std::min(mn, (int) ans2.length());
            }
        }

        std::cout << "mn: " << mn << '\n';
    }

    return 0;
}
