#include <iostream>
#include <string>
#include <vector>

using ll = long long;

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

    ll A, B, C;
    std::vector<ll> program;

    std::string s;
    while (getline(std::cin, s)) {
        if (s.find("Register A:") != std::string::npos) {
            A = stoll(s.substr(s.find(':') + 2));
        } else if (s.find("Register B:") != std::string::npos) {
            B = stoll(s.substr(s.find(':') + 2));
        } else if (s.find("Register C:") != std::string::npos) {
            C = stoll(s.substr(s.find(':') + 2));
        } else if (s.find("Program:") != std::string::npos) {
            s = s.substr(s.find(':') + 2);
            auto vals = split(s, ',');
            for (auto &str : vals)
                program.emplace_back(stoll(str));
        }
    }

    int idx = 0;
    std::vector<ll> output;

    while (idx < (int) program.size()) {
        ll opcode = program[idx];
        ll operand = program[idx + 1];

        auto combo = [&](int x) {
            if (x <= 3)
                return (char) (x + '0');
            if (x == 4)
                return 'A';
            if (x == 5)
                return 'B';
            return 'C';
        };

        if (opcode == 0) {
            printf("A = A >> %c\n", combo(operand));
        } else if (opcode == 1) {
            printf("B = B ^ %lld\n", operand);
        } else if (opcode == 2) {
            printf("B = %c mod 8\n", combo(operand));
        } else if (opcode == 3) {
            if (A != 0) {
                printf("idx = %lld\n", operand);
                exit(0);
                continue;
            }
        } else if (opcode == 4) {
            printf("B = B ^ C\n");
        } else if (opcode == 5) {
            printf("output %c mod 8\n", combo(operand));
        } else if (opcode == 6) {
            printf("B = A >> %c\n", combo(operand));
        } else if (opcode == 7) {
            printf("C = A >> %c\n", combo(operand));
        }

        idx += 2;
    }

    return 0;
}
