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
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int N, X;
    cin >> N >> X;
    vector<int> weights(N);

    for (int &weight : weights)
        cin >> weight;

    sort(weights.begin(), weights.end());

    // debug(weights);
    int64_t answer = 0, capacity = 0, children = 0;
    int64_t start = 0, end = N - 1;
    bool second = false;

    for (int i = 0, j = N - 1; i <= j; i++) {
        if (weights[i] + weights[j] <= X) {
            answer++;
            j--;
            continue;
        }

        second = true;
        start = i, end = j;
        break;
    }

    for (int i = start; second && i <= end; i++) {
        capacity += weights[i];
        children++;

        if (children == 2 || capacity > X) {
            capacity = weights[i];
            children = 1;
            answer++;
        }
    }

    cout << answer << '\n';
}

/*
3 10
1 2 3

10 15
9 8 8 9 10 8 5 8 7 10

10 15
9 8 8 9 10 8 5 8 7 10


5 7 8 8 8 8 9 9 10 10

10 20
5 9 6 5 8 9 10 6 5 6

20
5 5 5 6 6 6 8 9 9 10
*/