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

template<typename Type>
void output_matrix(const vector<vector<Type>> &matrix) {  
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = 0; i < row; i++) 
        for (int j = 0; j < column; j++) 
            cout << boolalpha << matrix[i][j] << " \n"[j + 1 == column];
}

bool evaluate(vector<int> &numbers, int required_sum, int index, int sum) {
    if (sum == required_sum) 
        return true;

    if (sum > required_sum || index == numbers.size())
        return false;

    bool taken = evaluate(numbers, required_sum, index + 1, sum + numbers[index]);

    if (taken)
        return taken;

    return evaluate(numbers, required_sum, index + 1, sum);

};

int main() {
    int N;
    cin >> N;
    vector<int> numbers(N);

    for (int &number : numbers)
        cin >> number;  

    int sum;
    cin >> sum;
    vector<vector<bool>> dp(N + 1, vector<bool>(sum + 1, false));

    for (int i = 1; i <= N; i++) {
        if (numbers[i - 1] <= sum)
            dp[i][numbers[i - 1]] = numbers[i - 1] <= sum;

        for (int j = 0; j <= sum; j++) {
            if (dp[i - 1][j] == true && j + numbers[i - 1] <= sum) 
                dp[i][j + numbers[i - 1]] = true;

            dp[i][j] = dp[i][j] || dp[i - 1][j];
        }
    }

    bool possible = evaluate(numbers, sum, 0, 0);
    assert(dp[N][sum] == possible);

    output_matrix(dp);
    cout << (dp[N][sum] ? "YES" : "NO") << '\n';
}

/*
5
1 2 49 3 4
8
*/