#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>

using ll = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::set<std::string> st;
    std::string s;
    bool first = true;
    ll res = 0;

    while (std::getline(std::cin, s)) {
        if (s.empty())
            continue;

        if (first) {
            std::string cur;
            for (auto &ch : s) {
                if (ch == ',') {
                    if (!cur.empty())
                        st.emplace(cur);
                    cur = "";
                } else {
                    if (ch == ' ')
                        continue;
                    if (cur.empty())
                        cur = ch;
                    else
                        cur += ch;
                }
            }
            if (!cur.empty())
                st.emplace(cur);
            first = false;

        } else {
            int n = (int) s.length();
            std::map<int, ll> dp;

            const auto solve = [&](auto &&self, int idx) -> ll {
                if (idx == n)
                    return 1ll;
                if (dp.count(idx))
                    return dp[idx];

                std::string cur;
                for (int i = idx; i < n; i++) {
                    cur += s[i];
                    if (st.count(cur))
                        dp[idx] += self(self, i + 1);
                }
                return dp[idx];
            };

            res += solve(solve, 0);
        }
    }

    std::cout << res << '\n';
    return 0;
}