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

#ifdef LOCAL
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

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

void run_case() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);

    for (int &a : A)
        cin >> a;

    for (int &b : B)
        cin >> b;

    vector<vector<bool>> defeated(N, vector<bool>(N, false));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j) 
                defeated[i][j] = A[i] > A[j] || B[i] > B[j];

    vector<int> strength(N, 0);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            strength[i] += defeated[i][j];

    cout << count(strength.begin(), strength.end(), *max_element(numbers.begin(), numbers.end())) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}