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

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int64_t N, M;
    cin >> N >> M;
    vector<int64_t> trees(N);

    for (int64_t &tree : trees)
        cin >> tree;

    int64_t low = 0, high = *max_element(trees.begin(), trees.end()) + 2;

    auto evaluate = [&](int height) -> bool {
        int64_t wood = 0;

        for (int64_t tree : trees)
            wood += max<int64_t>(0, tree - height);

        return wood >= M;
    };

    int64_t answer = 0;

    while (low <= high) { 
        int64_t mid = low + (high - low) / 2;

        if (evaluate(mid)) {
            low = mid + 1;
            answer = mid;
        } else {
            high = mid - 1;
        }
    }

    cout << answer << '\n';
}
/*
4 7
20 15 10 17

5 7
10 13 15 17 20
0  1  2  3

5 20
4 42 40 26 46

62 52 37 20 -> suffix sums

_  + _ + 17 + 20
*/ 