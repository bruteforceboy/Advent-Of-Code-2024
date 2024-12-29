#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::vector<std::string>> vals;
    std::string s;
    std::vector<std::tuple<int, int, int, int>> coords;

    while (getline(std::cin, s)) {
        int cur = 0;
        std::vector<int> vals;
        bool in = false, neg = false;
        for (auto &str : s) {
            if (str == '-') {
                neg = true;
            } else if (!isdigit(str)) {
                if (in) {
                    if (neg)
                        vals.emplace_back(-cur);
                    else
                        vals.emplace_back(cur);
                }
                cur = 0;
                in = false;
                neg = false;
            } else {
                in = true;
                cur = (cur * 10) + (str - '0');
            }
        }
        if (in) {
            if (neg)
                vals.emplace_back(-cur);
            else
                vals.emplace_back(cur);
        }
        int sx = vals[0], sy = vals[1];
        int dx = vals[2], dy = vals[3];
        std::swap(sx, sy);
        std::swap(dx, dy);
        coords.emplace_back(sx, sy, dx, dy);
    }

    constexpr int n = 103;
    constexpr int m = 101;

    for (int ITER = 0; ITER < 101 * 103; ITER++) {
        for (auto &[sx, sy, dx, dy] : coords) {
            sx = (sx + dx) % n, sx += n, sx %= n;
            sy = (sy + dy) % m, sy += m, sy %= m;
        }
        std::set<std::pair<int, int>> st;
        for (auto &[sx, sy, _, __] : coords)
            st.emplace(sx, sy);
        if ((int) st.size() == (int) coords.size()) {
            std::cout << ITER << std::endl;
            exit(0);
        }
    }

    return 0;
}