#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>

using namespace std;

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

void debug_out() {
    cerr << endl;
}

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) 
        os << other[i] << ", ";
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

// const set<vector<string>> shapes = {{"*.", "**"}, {"**", "*."}, {".*", "**"}, {"**", ".*"}};
const int DIRS = int(4);
const int DR[] = {+1, 0, -1, 0};
const int DC[] = {0, -1, 0, +1};
const int DDR[] = {+1, +1, -1, -1};
const int DDC[] = {+1, -1, +1, -1};
const int INF = int(1e9 + 5);

void run_case() {
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);

    for (auto &row : grid)
        cin >> row;

    vector<vector<bool>> visited(N, vector<bool>(M, false));
    bool all_L_shaped = true;
    int min_r = INF, min_c = INF, max_r = -INF, max_c = -INF;
    int stars = 0;

    auto valid = [&](int row, int column) -> bool {
        return row >= 0 && row < N && column >= 0 && column < M;
    };

    auto Dfs = y_combinator([&](auto dfs, int row, int column) -> void {
        if (!valid(row, column) || visited[row][column] || grid[row][column] == '.')
            return;

        visited[row][column] = true;
        stars++;
        min_r = min(row, min_r);
        max_r = max(row, max_r);
        min_c = min(column, min_c);
        max_c = max(column, max_c);

        for (int d = 0; d < DIRS; d++)
            dfs(row + DR[d], column + DC[d]);
    });

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (!visited[i][j] && grid[i][j] == '*') {
                stars = 0;
                min_r = i, max_r = i; 
                min_c = j, max_c = j;
                Dfs(i, j);

                all_L_shaped = all_L_shaped && stars == 3 && (max_r - min_r + 1 == 2 && max_c - min_c + 1 == 2);

                if (all_L_shaped) {
                    for (int r = min_r; r <= max_r; r++)
                        for (int c = min_c; c <= max_c; c++)
                            if (grid[r][c] == '*') {
                                for (int d = 0; d < 4; d++) {
                                    if (valid(r + DDR[d], c + DDC[d]) && grid[r + DDR[d]][c + DDC[d]] == '*') {
                                        if (r + DDR[d] >= min_r && r + DDR[d] <= max_r && c + DDC[d] >= min_c && c + DDC[d] <= max_c)
                                            continue;

                                        all_L_shaped = false;
                                        break;
                                    }
                                }
                            }
                }
            }

    cout << (all_L_shaped ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}