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

const int ALPHABET = int(26);
const char MIN_CHAR = char('a');
const int INF = int(1e9 + 5);

void run_case(int test_case) {
    string S, F;
    cin >> S >> F;
    int answer = 0;
    vector<bool> present(ALPHABET, false);

    for (int i = 0; i < F.length(); i++) 
        present[F[i] - MIN_CHAR] = true;

    for (int i = 0; i < S.length(); i++) {
        if (present[S[i] - MIN_CHAR]) 
            continue;

        int start = S[i] - MIN_CHAR;
        int cost = INF;
        int left = -1, right = -1;

        for (int i = start; i < ALPHABET; i++) 
            if (present[i]) {
                cost = min(cost, abs(i - start));
                right = i;
            }

        for (int i = start; i >= 0; i--) 
            if (present[i]) {
                cost = min(cost, start - i);
                left = i;
            }

        if (right != -1)
            cost = min(cost, ALPHABET - right + start);
        if (left != -1)
            cost = min(cost, left + ALPHABET - start);

        assert(cost != INF);
        answer += cost;
    }

    cout << "Case #" << test_case << ": " << answer << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif  

    int tests;
    cin >> tests;

    for (int test = 1; test <= tests; test++) 
        run_case(test);
}

/*
1
ab
zy
*/