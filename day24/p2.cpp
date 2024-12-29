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

    long long val1 = 0, val2 = 0, pw1 = 1, pw2 = 1;

    while (getline(std::cin, s)) {
        if (s.empty()) {
            read_formula = true;
            continue;
        }
        if (!read_formula) {
            auto val = split(s, ':');
            auto num = stoll(val[1].substr(val[1].find(' ') + 1));
            if (val[0][0] == 'x')
                val1 = val1 + pw1 * num, pw1 <<= 1;
            else
                val2 = val2 + pw2 * num, pw2 <<= 1;
            vals[val[0]] = num;
        } else {
            auto val = split(s, ' ');
            trace[val.back()].emplace_back(val[0], val[1], val[2]);
        }
    }

    long long total = val1 + val2;

    const auto swap_vals = [&](std::string i, std::string j) {
        auto tmp = trace[j];
        trace[j] = trace[i];
        trace[i] = tmp;
    };

    swap_vals("z07", "vmv");
    swap_vals("z20", "kfm");
    swap_vals("tqr", "hth");
    swap_vals("hnv", "z28");
    // hnv, hth, kfm, tqr, vmv, z07, z20, z28, bingo!!

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

    std::cout << "result: " << result << std::endl;
    std::cout << "total: " << total << std::endl;
    std::cout << std::bitset<46>(val1).to_string() << std::endl;
    std::cout << std::bitset<46>(val2).to_string() << std::endl;
    std::cout << std::bitset<46>(result).to_string() << std::endl;
    std::cout << std::bitset<46>(total).to_string() << std::endl;

    auto get_pattern = [&](auto &&self, std::string bt, long long dep) {
        if (bt[0] == 'x' || bt[0] == 'y')
            return bt;
        if (dep == 2)
            return bt;
        std::string ret;
        for (auto &[x, y, z] : trace[bt]) {
            ret += "(" + self(self, x, dep + 1) + " " + y + " " +
                   self(self, z, dep + 1) + ")";
        }
        return ret;
    };

    for (auto &str : order) {
        std::cout << "pattern for: " << str
                  << " is: " << get_pattern(get_pattern, str, 0) << std::endl;
    }
    return 0;
}