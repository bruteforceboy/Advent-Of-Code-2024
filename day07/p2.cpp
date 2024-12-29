#include <algorithm>
#include <iostream>
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

    std::vector<std::vector<std::string>> vals;
    std::string s;
    long long res = 0;

    while (getline(std::cin, s)) {
        auto target = stoll(s.substr(0, s.find(':')));
        s = s.substr(s.find(':') + 1);
        auto vals = split(s, ' ');
        int n = static_cast<int>(vals.size()) - 1;

        std::vector<std::vector<std::string>> all;
        std::vector<std::string> v;
        const auto solve = [&](auto &&self, int idx) -> void {
            if (idx == n) {
                all.push_back(v);  // retarrr*, I should prune but my pc!!
                return;
            }
            v.emplace_back("x");
            self(self, idx + 1);
            v.pop_back();
            v.emplace_back("*");
            self(self, idx + 1);
            v.pop_back();
            v.emplace_back("+");
            self(self, idx + 1);
            v.pop_back();
        };
        solve(solve, 0);

        bool ok = false;
        for (auto &lst : all) {
            long long cur = stoll(vals[0]), idx = 1;

            for (auto &st : lst) {
                if (st == "*")
                    cur *= stoll(vals[idx]);
                else if (st == "+")
                    cur += stoll(vals[idx]);
                else
                    cur = stoll(std::to_string(cur) + vals[idx]);
                if (cur > target)
                    break;
                ++idx;
            }

            if (cur == target)
                ok = true;
        }

        if (ok)
            res += target;
    }

    std::cout << res << '\n';
    return 0;
}