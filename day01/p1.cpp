#include <algorithm>
#include <iostream>
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
    std::vector<std::vector<std::string>> vals;
    std::string s;
    std::vector<int> left, right;
    while (getline(std::cin, s)) {
        auto vals = split(s, ' ');
        left.emplace_back(stoll(vals[0]));
        right.emplace_back(stoll(vals[1]));
    }
    std::ranges::sort(left);
    std::ranges::sort(right);
    int tot = 0;
    for (int i = 0; i < (int) left.size(); i++)
        tot += abs(left[i] - right[i]);
    std::cout << tot << '\n';
    return 0;
}
