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
            cout << setw(4) << (matrix[i][j] >= INF ? "INF" : to_string(matrix[i][j])) << " \n"[j + 1 == column];
}

int main() {
    cout << "Enter the number of vertices" << '\n';

    int vertices;
    cin >> vertices;
    vector<vector<int>> adjacency_matrix(vertices, vector<int>(vertices, 0));

    cout << "Enter the adjacency matrix (0, weight)" << '\n';   // 0 means there does not exist an edge

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            cin >> adjacency_matrix[i][j];

    vector<vector<int>> dp = adjacency_matrix;

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            if (i != j && dp[i][j] == 0)
                dp[i][j] = INF;

    for (int k = 0; k < vertices; k++)
        for (int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

    output_matrix(dp);
}

/*
4
0 5 0 10 
0 0 3 0 
0 0 0 1 
0 0 0 0
*/