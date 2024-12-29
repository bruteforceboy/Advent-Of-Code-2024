#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using ll = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    ll res = 0;
    std::map<std::tuple<ll, ll, ll, ll>, ll> cnt;

    while (std::getline(std::cin, s)) {
        ll val = std::stoll(s);
        std::vector<ll> cur{0};
        std::vector<ll> vals;

        for (ll i = 0; i < 2001; i++) {
            cur.emplace_back(val % 10);
            vals.push_back(val % 10);

            ll mix1 = val * 64;
            val ^= mix1;
            val %= 16777216;

            ll mix2 = val / 32;
            val ^= mix2;
            val %= 16777216;

            ll mix3 = val * 2048;
            val ^= mix3;
            val %= 16777216;
        }

        std::vector<ll> diff;
        for (ll i = 1; i < (ll) cur.size(); i++)
            diff.emplace_back(cur[i] - cur[i - 1]);

        std::map<std::tuple<ll, ll, ll, ll>, ll> mp;
        for (ll i = 0; i + 3 < (ll) diff.size(); i++) {
            auto key =
                std::make_tuple(diff[i], diff[i + 1], diff[i + 2], diff[i + 3]);
            if (!mp.count(key))
                mp[key] = vals[i + 3];
        }

        for (auto &[key, value] : mp)
            cnt[key] += value;
    }

    for (auto &[key, value] : cnt)
        res = std::max(res, value);

    std::cout << res << '\n';
    return 0;
}
