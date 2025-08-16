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
        os << other[i] << ' ';
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

const int INF = int(1e9 + 5);

template<typename Type>
void output_matrix(vector<vector<Type>> &matrix, int start = 0) {
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = start; i < row; i++) 
        for (int j = start; j < column; j++) 
            cerr << setw(4) << (matrix[i][j] == INF ? "INF" : to_string(matrix[i][j])) << " \n"[j + 1 == column];
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adjacency_matrix(N, vector<int>(M, 0));
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            cin >> adjacency_matrix[i][j];
        }

    auto valid = [&](int row, int column) -> bool {
        return row < N && row >= 0 && column < M && column >= 0;
    };

    y_combinator([&](auto dfs, int row, int column) -> void {
        if (!valid(row, column) || visited[row][column] || adjacency_matrix[row][column] == -1)
            return;

        visited[row][column] = true;
        dfs(row + 1, column);
        dfs(row, column + 1);
    })(0, 0);

    if (visited[N - 1][M - 1] == false) {
        cout << 0 << '\n'; 
        return 0;
    }

    vector<vector<int>> down_dp(N + 1, vector<int>(M + 1, 0));
    vector<vector<int>> up_dp(N + 1, vector<int>(M + 1, 0));
    vector<vector<bool>> path(N + 1, vector<bool>(M + 1, 0));         // this stores the path used at every step of the way

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (adjacency_matrix[i - 1][j - 1] == -1) 
                continue;

            path[i][j] = down_dp[i - 1][j] > down_dp[i][j - 1];      // 1 means go up, 0 means go left
            down_dp[i][j] = adjacency_matrix[i - 1][j - 1] + max(down_dp[i - 1][j], down_dp[i][j - 1]);
        }
    }

    if (down_dp[N][M] <= 0) {
        cout << 0 << '\n';
        return 0;
    }

    int up_index = N, left_index = M;

    while (true) {
        assert(left_index >= 0 && up_index >= 0);
        adjacency_matrix[up_index - 1][left_index - 1] = 0;

        if (path[up_index][left_index]) {
            up_index--;
        } else {
            left_index--;
        }

        if (up_index == 0 || left_index == 0)
            break;
    }

    adjacency_matrix[0][0] = 0;

    for (int i = N - 1; i >= 0; i--) {
        for (int j = M - 1; j >= 0; j--) {
            if (adjacency_matrix[i][j] == -1) 
                continue;

            up_dp[i][j] = adjacency_matrix[i][j] + max(up_dp[i + 1][j], up_dp[i][j + 1]);
        }
    }

    debug(down_dp[N][M], up_dp[0][0]);
    cout << down_dp[N][M] + up_dp[0][0] << '\n';
}

/*
4 4
0 0 -1 1
0 -1 1 1
0 0 1 1
1 1 1 1

5 5
0 0 0 1 1
1 1 1 1 1
0 0 1 1 1
0 0 1 1 1
1 0 0 1 1

4 4
1 0 0 0
1 0 0 0
1 0 0 0
1 0 1 1

[path is]
0    0    0    0    0
0    0    0    0    0
0    0    0    0    0
0    1    1    1    0
0    1    1    1    0

4
4
0 0 0 1
1 0 0 0
0 0 0 0
0 0 0 0
*/