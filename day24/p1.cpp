#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <ranges>
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
    bool read_formula = false;

    std::map<std::string, long long> vals;
    std::map<std::string,
             std::vector<std::tuple<std::string, std::string, std::string>>>
        trace;

    while (getline(std::cin, s)) {
        if (s.empty()) {
            read_formula = true;
            continue;
        }
        if (!read_formula) {
            auto val = split(s, ':');
            vals[val[0]] = stoll(val[1].substr(val[1].find(' ') + 1));
        } else {
            auto val = split(s, ' ');
            trace[val.back()].emplace_back(val[0], val[1], val[2]);
        }
    }

    std::map<std::string, std::vector<std::string>> adj;
    for (auto &[val, vec] : trace) {
        for (auto &[x, y, z] : vec) {
            adj[x].emplace_back(val);
            adj[z].emplace_back(val);
        }
    }
    std::map<std::string, bool> vis;
    std::vector<std::string> order;
    const auto dfs = [&](auto &&self, std::string src) -> void {
        vis[src] = true;
        for (auto &to : adj[src])
            if (!vis.count(to))
                self(self, to);
        order.emplace_back(src);
    };
    for (auto &[str, _] : adj)
        if (!vis.count(str))
            dfs(dfs, str);
    std::ranges::reverse(order);
    for (auto &str : order) {
        if (!vals.count(str)) {
            for (auto &[x, y, z] : trace[str]) {
                if (y == "AND")
                    vals[str] = (vals[x] & vals[z]);
                if (y == "OR")
                    vals[str] = (vals[x] | vals[z]);
                if (y == "XOR")
                    vals[str] = (vals[x] ^ vals[z]);
            }
        }
    }
    std::string str;
    for (auto &[_, val] : vals)
        if (_[0] == 'z')
            str += (char) (val + '0');
    std::ranges::reverse(str);
    long long result = 0;
    for (auto &ch : str) {
        result <<= 1;
        if (ch == '1')
            result += 1;
    }

    std::cout << result << '\n';

    return 0;
}