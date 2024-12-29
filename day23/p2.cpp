#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <vector>

using namespace std;

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

    std::string s;
    map<std::string, set<std::string>> adj;
    set<std::string> pts_st;
    while (getline(std::cin, s)) {
        auto pts = split(s, '-');
        adj[pts[0]].emplace(pts[1]);
        adj[pts[1]].emplace(pts[0]);
        pts_st.emplace(pts[0]);
        pts_st.emplace(pts[1]);
    }

    set<std::vector<std::string>> st;
    std::vector<std::string> ans;
    // sloowwwwww, but whatever
    for (auto &[n, vals] : adj) {
        int sz = static_cast<int>(vals.size());

        std::vector<std::string> neighs(begin(vals), end(vals));

        for (int i = 0; i < (1 << sz); i++) {
            std::vector<std::string> cur{n};
            for (int j = 0; j < sz; j++)
                if ((i & (1 << j)))
                    cur.emplace_back(neighs[j]);

            bool ok = true;
            for (auto x : cur) {
                for (auto y : cur) {
                    if (x != y && !adj[x].count(y)) {
                        ok = false;
                        break;
                    }
                }
                if (!ok)
                    break;
            }

            if (ok) {
                ranges::sort(cur);
                if (cur.size() > ans.size())
                    ans = cur;
            }
        }
    }

    for (auto &str : ans)
        std::cout << str << ',';
    std::cout << endl;

    return 0;
}