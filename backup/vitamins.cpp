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

#ifdef LOCAL
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

const int MASK = int(1 << 3);
const int INF = int(1e9 + 5);
const int FULL = int(MASK - 1);
const char MIN_CHAR = char('A');

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int N;
    cin >> N;
    vector<int> cost(MASK, INF);
    cost[0] = 0;

    for (int i = 0; i < N; i++) {
        int price, state = 0;
        string vitamins;
        cin >> price >> vitamins;

        for (char vitamin : vitamins) {
            int bit = vitamin - MIN_CHAR;
            state |= 1 << bit;
        }

        cost[state] = min(cost[state], price);
    }

    int answer = INF;

    for (int mask = FULL; mask > 0; mask--) {
        int price = cost[mask];

        for (int bit = 1; bit <= 3; bit++) {
            if (!(mask & (1 << bit))) {
                for (int i = 0; i < MASK; i++) {
                    if (mask & (1 << bit)) {
                        price += cost[i];
                    }
                }
            }
        }

        answer = min(answer, price);
    }

    cout << (answer >= INF ? -1 : answer) << '\n';
}