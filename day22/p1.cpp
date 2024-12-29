#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    long long res = 0;

    while (std::getline(std::cin, s)) {
        long long val = std::stoll(s);
        for (int i = 0; i < 2000; i++) {
            auto mix1 = val * 64;
            val ^= mix1;
            val %= 16777216;

            auto mix2 = val / 32;
            val ^= mix2;
            val %= 16777216;

            auto mix3 = val * 2048;
            val ^= mix3;
            val %= 16777216;
        }
        res += val;
    }

    std::cout << res << '\n';
    return 0;
}
