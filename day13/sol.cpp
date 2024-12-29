#include <algorithm>
#include <iostream>
#include <string>

using ll = long long;

std::pair<ll, ll> solve(ll a, ll b, ll c, ll d, ll u, ll v) {
    ll y = ((u * c) - (v * a)) / ((c * b) - (d * a));
    ll x = (u - b * y) / a;

    if (a * x + b * y == u && c * x + d * y == v)
        return std::make_pair(x, y);
    else
        return std::make_pair(-1, -1);
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string s;

    std::vector<std::pair<ll, ll>> vals;
    ll ans = 0;
    while (getline(std::cin, s)) {
        if (s.empty())
            continue;
        bool prize = (s[0] == 'P');
        s = s.substr(s.find(':') + 1);
        s += '.';

        std::vector<std::pair<ll, ll>> vec;
        std::vector<ll> nums;
        ll cur_num = 0;
        for (auto &ch : s) {
            if (!isdigit(ch)) {
                if (cur_num)
                    nums.emplace_back(cur_num);
                cur_num = 0;
            } else if (isdigit(ch)) {
                cur_num = (cur_num * 10) + (ch - '0');
            }
        }

        if (cur_num)
            nums.emplace_back(cur_num);
        if (!prize)
            vals.emplace_back(nums[0], nums[1]);
        if (prize) {
            auto res = solve(vals[0].first, vals[1].first, vals[0].second,
                             vals[1].second, 10000000000000ll + nums[0],
                             10000000000000ll + nums[1]);
            if (res.first != -1)
                ans += res.first * 3 + res.second;
            vals.clear();
        }
    }

    std::cout << ans << '\n';

    return 0;
}