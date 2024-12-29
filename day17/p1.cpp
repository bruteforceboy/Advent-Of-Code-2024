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

    auto combo = [&](int x) -> ll {
        if (x <= 3)
            return x;
        if (x == 4)
            return A;
        if (x == 5)
            return B;
        return C;
    };

    int idx = 0;
    std::vector<int> output;

    while (idx < (int) program.size()) {
        int opcode = program[idx];
        int operand = program[idx + 1];
        if (opcode == 0) {
            A = A >> combo(operand);
        } else if (opcode == 1) {
            B = B ^ operand;
        } else if (opcode == 2) {
            B = combo(operand) & 7;
        } else if (opcode == 3) {
            if (A != 0) {
                idx = operand;
                continue;
            }
        } else if (opcode == 4) {
            B = B ^ C;
        } else if (opcode == 5) {
            output.push_back(combo(operand) & 7);
        } else if (opcode == 6) {
            B = A >> combo(operand);
        } else if (opcode == 7) {
            C = A >> combo(operand);
        }

        idx += 2;
    }

    for (auto &out : output)
        std::cout << out << ",";

    return 0;
}
