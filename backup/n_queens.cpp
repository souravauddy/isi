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
#include <ranges>

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

int main() {
    int N;
    cin >> N;
    vector<vector<bool>> board(N, vector<bool>(N, false));
    vector<int> queen_position(N);

    auto valid_position = [&](int row, int column) -> bool {
        for (int i = row; i >= 0; i--)
            if (board[i][column])
                return false;
        
        for (int i = row, j = column; i >= 0 && j >= 0; i--, j--)
            if (board[i][j])
                return false;

        for (int i = row, j = column; i >= 0 && j < N; i--, j++)
            if (board[i][j])
                return false;

        return true;
    };

    bool possible = y_combinator([&](auto self, int row) -> bool {
        if (row == N) {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++) 
                    cout << (board[i][j] ? "Q" : ".") << " \n"[j + 1 == N];

            return true;
        }

        bool success = false;

        for (int i = 0; i < N; i++) {
            if (valid_position(row, i)) {
                board[row][i] = true;
                queen_position[i] = row;
                success = self(row + 1);
                board[row][i] = false;  // backtracking
            } 

            if (success)
                return true;
        }

        return success;
    })(0);

    if (!possible) {
        cout << "It is not possible to place the queens" << '\n';
        return 0;
    }

    for (int i = 0; i < N; i++)
        cout << queen_position[i] + 1 << ' ';
    cout << '\n';

    for (int i = 0; i < N; i++)
        cout << i + 1 << ' ';
    cout << '\n';
}

// 1 1 1 1 
// 1 1 1 1
// 1 1 1 1
// 1 1 1 1