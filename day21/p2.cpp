#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// cancer🙏

using ll = long long;

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

    std::vector<ll> vals;
    while (std::getline(std::cin, code)) {
        int x = 3, y = 2;
        std::vector<std::string> ans;
        for (auto &ch : code) {
            auto [tx, ty] = get_pos(ch, grid);
            std::vector<std::string> ways;
            std::string cur;
            const auto get_ways = [&](auto &&self, int x, int y, int tx,
                                      int ty) {
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
                for (auto &str1 : ans) {
                    for (auto &str2 : ways) {
                        std::string cur = str1 + str2;
                        nans.emplace_back(str1 + str2);
                    }
                }
                ans = nans;
            }
        }

        const auto solve = [&](int x, int y, std::string str) {
            std::vector<std::string> ans;
            for (auto &ch : str) {
                auto [tx, ty] = get_pos(ch, grid2);
                std::vector<std::string> ways;
                std::string cur;
                const auto get_ways = [&](auto &&self, int x, int y, int tx,
                                          int ty) {
                    if (grid2[x][y] == '0')
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
                    for (auto &str1 : ans) {
                        for (auto &str2 : ways) {
                            std::string cur = str1 + str2;
                            nans.emplace_back(str1 + str2);
                        }
                    }
                    ans = nans;
                }
            }
            return ans;
        };

        std::map<std::pair<std::string, int>, ll> dp;
        const auto get_ans = [&](auto &&self, std::string str, int itr) -> ll {
            if (itr == 0)
                return (ll) str.length();

            if (dp.count(std::make_pair(str, itr)))
                return dp[std::make_pair(str, itr)];
            ll res = std::numeric_limits<ll>::max();

            std::string first_to;
            first_to += str[0];
            for (auto &combo : solve(0, 2, first_to))
                res = std::min(res, self(self, combo, itr - 1));

            for (int i = 1; i < (int) str.length(); i++) {
                auto [sx, sy] = get_pos(str[i - 1], grid2);
                ll cur = std::numeric_limits<ll>::max();
                std::string to;
                to += str[i];
                for (auto &combo : solve(sx, sy, to))
                    cur = std::min(cur, self(self, combo, itr - 1));
                res += cur;
            }

            return dp[std::make_pair(str, itr)] = res;
        };

        ll mn = std::numeric_limits<ll>::max();
        for (auto &cur_str : ans)
            mn = std::min(mn, get_ans(get_ans, cur_str, 25));

        vals.emplace_back(mn);
    }
    std::cout << vals[0] * 140LL + vals[1] * 170LL + vals[2] * 169LL +
                     vals[3] * 803LL + vals[4] * 129LL
              << std::endl;
    return 0;
}