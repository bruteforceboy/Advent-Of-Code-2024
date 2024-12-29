#include <algorithm>
#include <iostream>
#include <map>
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

using ll = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::vector<std::string>> vals;
    std::string s;

    while (getline(std::cin, s)) {
        auto vals = split(s, ' ');
        std::map<std::string, ll> mp;
        for (auto &str : vals)
            ++mp[str];
        constexpr int ITER = 75;
        for (int i = 0; i < ITER; i++) {
            std::map<std::string, ll> nvals;
            for (auto &[val, cnt] : mp) {
                int m = (int) val.size();
                if (val == "0") {
                    nvals["1"] += cnt;
                } else if (m % 2) {
                    nvals[std::to_string(stoll(val) * 2024)] += cnt;
                } else {
                    nvals[std::to_string(stoll(val.substr(0, m / 2)))] += cnt;
                    nvals[std::to_string(stoll(val.substr(m / 2)))] += cnt;
                }
            }
            mp = std::move(nvals);
        }
        ll res = 0;
        for (auto &[x, y] : mp)
            res += y;
        std::cout << res << '\n';
    }

    return 0;
}