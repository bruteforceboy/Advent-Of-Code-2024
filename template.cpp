#include <bits/stdc++.h>
using namespace std;

auto split(string str, char delim) -> vector<string> {
    vector<string> res;
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

// be sure the input is either multiline/singleline
// you may need some local variables to be global

template <typename T>
void rotateCW(vector<vector<T>> &grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<T>> ngrid(m, vector<T>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ngrid[j][n - i - 1] = grid[i][j];
    grid = ngrid;
}

template <typename T>
void rotateCCW(vector<vector<T>> &grid) {
    for (int i = 0; i < 3; i++)
        rotateCW(grid);
}

/*
 * translates a vector to start from top left
 * default_value is usually the empty/0 value in the grid
 * Sample grid
 * ..#..
 * ...#.
 * ...##
 * Output grid
 * #....
 * .#...
 * .##..
 */
template <typename T>
void normalize(vector<vector<T>> &grid, T default_value) {
    const int inf = numeric_limits<int>::max();
    int si = inf, sj = inf, ei = -inf, ej = -inf;
    int n = (int) grid.size(), m = (int) grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != default_value) {
                si = min(si, i);
                sj = min(sj, j);
                ei = max(ei, i);
                ej = max(ej, j);
            }
        }
    }
    int nn = ei - si + 1, nm = ej - sj + 1;
    vector<vector<T>> ng(n, vector<T>(m, default_value));
    for (int i = 0; i < nn; i++)
        for (int j = 0; j < nm; j++)
            ng[i][j] = grid[i + si][j + sj];
    grid = ng;
}

// be sure the input is either multiline/singleline
// you may need some local variables to be global

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<string>> vals;
    string s;
    while (getline(cin, s))
        vals.emplace_back(split(s, ','));  // change the delimeter
    return 0;
}
