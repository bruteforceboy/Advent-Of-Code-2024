#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::vector<std::string>> vals;
    std::string s;

    while (getline(std::cin, s)) {
        std::vector<int> vals;
        for (auto &ch : s)
            vals.emplace_back(ch - '0');

        std::vector<std::pair<int, int>> str;
        int idx = 0;
        for (int i = 0; i < (int) vals.size(); i++) {
            if (i % 2 == 1) {
                str.emplace_back(vals[i], -1);
            } else {
                str.emplace_back(vals[i], idx);
                ++idx;
            }
        }

        int m = static_cast<int>(str.size()), ptr = 0;

        std::vector<std::vector<std::pair<int, int>>> nxt(m);
        std::vector<bool> moved(m);

        for (int i = m - 1; i >= 0; i--) {
            if (str[i].second == -1)
                continue;
            for (int j = 0; j < i; j++) {
                if (str[j].second == -1 && str[j].first >= str[i].first) {
                    nxt[j].emplace_back(str[i].second, str[i].first);
                    str[j].first -= str[i].first;
                    str[i].second = -1;
                    break;
                }
            }
        }

        std::vector<int> nstr;
        for (int i = 0; i < m; i++) {
            for (auto [x, y] : nxt[i])
                for (int itr = 0; itr < y; itr++)
                    nstr.emplace_back(x);
            for (int itr = 0; itr < str[i].first; itr++)
                nstr.emplace_back(str[i].second);
        }

        for (auto &val : nstr)
            std::cout << val << ' ';
        std::cout << std::endl;

        int block = 0;
        long long res = 0;
        for (int i = 0; i < (int) nstr.size(); i++)
            if (nstr[i] != -1)
                res += 1ll * i * nstr[i];

        std::cout << res << std::endl;
    }
    return 0;
}