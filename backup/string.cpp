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

int f(int a, int b) {
    if ((a ^ b) < (b + a) && (b - 4) > (a ^ b)) {
        a = b + 2;
        a = b + 1;
        a = b + 1;

        return f(b + 2, b + 1) + f(a, b + a);
    }

    return b;
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int a = 8, b = 9;
    cout << f(a, b) << '\n';

    // int a = 3, b = 5, c = 10;

    // if ((c + a) < (b - c)) {
    //     c = (c + 8) + b;
    // }

    // if (4 > b && (c & b) < b) {
    //     c = (a + 7) + b;
    // } else {
    //     c = a & c;
    // }

    // cout << a + b + c << '\n';
}