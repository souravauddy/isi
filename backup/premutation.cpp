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

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

template<typename Type>
void output_matrix(vector<vector<Type>> &matrix, int start = 0) {
    const int row = matrix.size();
    const int column = matrix[0].size();
    const int INF = int(1e9 + 5);

    for (int i = start; i < row; i++) 
        for (int j = start; j < column; j++) 
            cout << setw(4) << (matrix[i][j] == INF ? "INF" : to_string(matrix[i][j])) << " \n"[j + 1 == column];
}

void run_case() {
    int N;
    cin >> N;
    vector<vector<int>> matrix(N, vector<int>(N - 1, 0));
    vector<int> permutation(N + 1);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - 1; j++)
            cin >> matrix[i][j];

    /*

    for (int i = 0; i < N - 1; i++) {
        vector<int> frequency(N + 1, 0);

        for (int j = 0; j < N; j++)
            frequency[matrix[j][i]]++;

        for (int k = 0; k <= N; k++)
            if (2 * frequency[k] >= N) {
                assert(k > 0);
                permutation[i] = k;
            }
    }

    unordered_set<int> all;
    for (int i = 0; i < N; i++)
        all.insert(i + 1);

    for (int i = 0; i < N - 1; i++)
        all.erase(permutation[i]);

    assert(all.size() == 1);
    int element = *all.begin();

    vector<int> frequency(N + 1);
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - 2; j++) {
            if (matrix[i][j + 1] == element)
                frequency[matrix[i][j]]++;
        }

    int position = 0;
    int count = 0;
    int element_ = -1;

    for (int k = 0; k <= N; k++) {
        if (frequency[k] > count) {
            element_ = k;
            count = frequency[k];
        }
    }

    if (element_ == -1)
        permutation.insert(permutation.begin(), element);
    else {
        for (int i = 0; i < N - 1; i++)
            if (permutation[i] == element_) {
                permutation.insert(permutation.begin() + i + 1, element);
                break;
            }
    }

    assert(permutation.size() == N);
    output_vector(permutation);
    */

    // The above solution is way too complicated
    // better solution


    vector<int> frequency(N + 1);

    for (int i = 0; i < N; i++)
        frequency[matrix[i][0]]++;

    int max = -1;

    for (int k = 0; k <= N; k++)
        if (frequency[k] > max) {
            max = frequency[k];
            permutation[0] = k;
        }

    for (int i = 0; i < N - 1; i++)
        if (matrix[0][i] != permutation[0]) {
            for (int j = 0; j < N; j++) {
                permutation[j + 1] = matrix[j][i];
            }

            break;
        }
    
    output_vector(permutation);
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

/*
5
4
4 2 1
4 2 3
2 1 3
4 1 3
3
2 3
1 3
1 2
5
4 2 1 3
2 1 3 5
4 2 3 5
4 1 3 5
4 2 1 5
4
2 3 4
1 3 4
1 2 3
1 2 4
3
2 1
1 3
2 3
*/