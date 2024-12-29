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
    int res = 0;
    while (getline(std::cin, s)) {
        auto vals = split(s, ' ');
        std::vector<int> v;
        for (auto &cur : vals)
            v.emplace_back(stoll(cur));
        bool ok1 = true;
        {
            for (int i = 1; i < (int) v.size(); i++)
                if (v[i] >= v[i - 1] || abs(v[i] - v[i - 1]) > 3)
                    ok1 = false;
        }
        bool ok2 = true;
        {
            for (int i = 1; i < (int) v.size(); i++)
                if (v[i] <= v[i - 1] || abs(v[i] - v[i - 1]) > 3)
                    ok2 = false;
        }
        res += ok1 || ok2;
    }

    std::cout << res << '\n';
    return 0;
}
