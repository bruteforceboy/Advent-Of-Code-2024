#include <algorithm>
#include <iostream>
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

    std::vector<std::vector<int>> vec;
    std::set<std::pair<int, int>> pr;

    while (getline(std::cin, s)) {
        if (s.empty())
            continue;
        if (s.find('|') != std::string::npos) {
            auto vals = split(s, '|');
            pr.emplace(stoll(vals[0]), stoll(vals[1]));
        } else {
            auto vals = split(s, ',');
            std::vector<int> cur;
            for (auto &str : vals)
                cur.emplace_back(stoll(str));
            vec.emplace_back(cur);
        }
    }

    int res = 0;
    for (auto &vals : vec) {
        bool ok = true;
        for (int i = 0; i < (int) vals.size() && ok; i++) {
            for (int j = i + 1; j < (int) vals.size(); j++) {
                if (pr.count(std::make_pair(vals[j], vals[i]))) {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            while (true) {
                bool found = false;
                for (int i = 0; i < (int) vals.size(); i++) {
                    for (int j = i + 1; j < (int) vals.size(); j++) {
                        if (pr.count(std::make_pair(vals[j], vals[i]))) {
                            found = true;
                            std::swap(vals[j], vals[i]);
                            break;
                        }
                    }
                }
                if (!found)
                    break;
            }
            res += vals[(int) vals.size() >> 1];
        }
    }

    std::cout << res;
    return 0;
}