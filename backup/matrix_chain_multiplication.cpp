#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <functional>
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

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
    const int size = other.size(); if (size <= 0) return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) os << other[i] << ' ';
    return os << other[size - 1] << ']';
} 

void debug_out() { cerr << endl; }  

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) { cerr << " [" << head << ']'; debug_out(args...); }

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

template<class Fun>
class y_combinator_result { 
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }


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
    int size;
    cout << "Enter the number of matrices" << '\n';
    cin >> size;
    vector<int> dimensions(size);

    for (int &d : dimensions)
        cin >> d;

    vector<vector<int>> dp(size, vector<int>(size, INF));
    vector<vector<int>> order(size, vector<int>(size, 0));

    for (int i = 0; i < size; i++) 
        dp[i][i] = 0;

    for (int row = 1; row < size; row++) {
        for (int i = 1; i < size - row + 1; i++) {
            const int j = i + row - 1;

            for (int k = i; k < j; k++) {
                int previous = dp[i][j];

                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + (dimensions[i - 1] * dimensions[k] * dimensions[j]));

                if (previous != dp[i][j]) 
                    order[i][j] = k;
            }
        }
    }

    cout << "The final output matrix is" << '\n';
    output_matrix(dp, true);

    cout << '\n' << "The parentthesis matrix is" << '\n'; 
    output_matrix(order, true);

    cout << '\n' << "The minimum cost for the scaler multiplication of the matrices is " << dp[1][size - 1] << '\n';
    cout << "The order of the parenthesis is" << '\n';

    char matrix_name = 'A';
    y_combinator([&](auto self, int start, int end) -> void {
        if (start == end) {
            cout << char(matrix_name + start - 1);
            return;
        }

        cout << '('; 
        self(start, order[start][end]);
        self(order[start][end] + 1, end);
        cout << ')';
    })(1, size - 1);

    cout << '\n';
}

/*
4
1 2 4 8

14
29 4 2 9 5 20 49 1 4 4524 2 49 54 59
*/