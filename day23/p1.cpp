#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <vector>

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
    std::map<std::string, std::set<std::string>> adj;
    while (getline(std::cin, s)) {
        auto pts = split(s, '-');
        adj[pts[0]].emplace(pts[1]);
        adj[pts[1]].emplace(pts[0]);
    }

    std::set<std::vector<std::string>> st;
    for (auto &[n, vals] : adj) {
        for (auto &n1 : vals) {
            for (auto &n2 : adj[n1])
                if (n2 != n1 && n2 != n && adj[n].count(n2)) {
                    std::vector<std::string> vals{n1, n, n2};
                    std::ranges::sort(vals);
                    st.emplace(vals);
                }
        }
    }

    int res = 0;
    for (auto &vec : st) {
        bool ok = false;
        for (auto &val : vec)
            if (val[0] == 't')
                ok = true;
        if (ok) {
            for (auto &val : vec)
                std::cout << val << ' ';
            std::cout << std::endl;
        }
        res += ok;
    }

    std::cout << res;

    return 0;
}