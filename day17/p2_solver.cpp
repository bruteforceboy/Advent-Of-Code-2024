#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<int> target_output = {2, 4, 1, 5, 7, 5, 0, 3,
                                      4, 0, 1, 6, 5, 5, 3, 0};

    const auto compute = [&](long long val, long long A) {
        long long B, C;
        A = (A << 3) + val;
        B = A % 8;
        B = B ^ 5;
        C = A >> B;
        A = A >> 3;
        B = B ^ C;
        B = B ^ 6;
        return B % 8;
    };

    std::reverse(begin(target_output), end(target_output));
    int sz = static_cast<int>(target_output.size());

    const auto solve = [&](auto &&self, int idx, long long A = 0) -> void {
        if (idx == sz) {
            std::cout << A << std::endl;
            exit(0);
        }
        for (int val = 0; val < 8; val++)
            if (compute(val, A) == target_output[idx])
                self(self, idx + 1, A * 8 + val);
    };

    solve(solve, 0);
    return 0;
}