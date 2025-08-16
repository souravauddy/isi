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
            cout << setw(4) << (matrix[i][j] == INF ? "INF" : to_string(matrix[i][j])) << " \n"[j + 1 == column];
}

int main() {
    int N;
    cin >> N;
    vector<vector<int>> matrix(N, vector<int>(N, 0));
    vector<bool> invalid(N, false);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> matrix[i][j];

    // now we just have to use dp, to improve the time complexity

    int determinant = y_combinator([&](auto self, int current_row) -> int {
        if (current_row == N - 2) {
            vector<vector<int>> _2d_matrix(2, vector<int>(2, 0));
            int row2 = 0, column2 = 0;

            for (int row = current_row; row < N; row++) {
                for (int column = 0; column < N; column++) 
                    if (!invalid[column]) 
                        _2d_matrix[row2][column2++] = matrix[row][column];

                row2++;
                column2 = 0;
            }

            assert(row2 == 2);

            return _2d_matrix[0][0] * _2d_matrix[1][1] - _2d_matrix[0][1] * _2d_matrix[1][0];
        }

        vector<int> co_factors(N - current_row);
        int index = 0;

        for (int column = 0; column < N; column++) {
            if (!invalid[column]) {
                invalid[column] = true;
                co_factors[index++] = self(current_row + 1);
                invalid[column] = false;
            }
        }

        int co_factor = 0, column = 0;

        for (int i = 0; i < N - current_row; i++) {
            while (invalid[column])
                column++;

            co_factor += (i % 2 == 0 ? 1 : -1) * matrix[current_row][column++] * co_factors[i];
        }
        
        return co_factor;
    })(0);

    debug(determinant);
    output_matrix(matrix);  
}

/*
3
1 0 0
0 1 0
0 0 1

4
1 2 9 3
4 2 4 5
6 2 7 8
4 5 9 2
*/