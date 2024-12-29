#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> vals;

    std::string s;
    while (getline(std::cin, s))
        vals.emplace_back(s);
    int x = -1, y = -1;
    int n = (int) vals.size();
    int m = (int) vals[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vals[i][j] == '^') {
                x = i;
                y = j;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            auto tmp = vals;
            int tx = x;
            int ty = y;
            if (vals[i][j] == '.') {
                vals[i][j] = '#';

                std::string dirs = "^>v<";
                std::set<std::pair<int, int>> st;
                std::set<std::set<std::pair<int, int>>> seen;
                bool loop = false;
                for (int itr = 0; itr < 10000; itr++) {
                    if (st.count(std::make_pair(x, y))) {
                        if (seen.count(st)) {
                            loop = true;
                            break;
                        } else {
                            seen.emplace(st);
                            seen.clear();
                        }
                    }
                    if (itr == 9999) {
                        loop = true;
                        break;
                    }
                    st.emplace(x, y);

                    int nx = x, ny = y;
                    if (vals[x][y] == '^')
                        --nx;
                    else if (vals[x][y] == '>')
                        ++ny;
                    else if (vals[x][y] == '<')
                        --ny;
                    else
                        ++nx;

                    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                        break;

                    if (vals[nx][ny] == '#') {
                        for (int idx = 0; idx < 4; idx++) {
                            if (vals[x][y] == dirs[idx]) {
                                vals[x][y] = dirs[(idx + 1) % 4];
                                break;
                            }
                        }
                        st.erase(std::make_pair(x, y));
                    } else {
                        vals[nx][ny] = vals[x][y];
                        vals[x][y] = 'X';
                        x = nx;
                        y = ny;
                    }
                }
                ans += loop;
            }
            vals = tmp;
            x = tx;
            y = ty;
        }
    }

    std::cout << ans;

    return 0;
}