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

    int N, teddy;
    cin >> N >> teddy;
    vector<int> chocolates(N), cost(N);

    for (int &chocolate : chocolates)   
        cin >> chocolate;

    for (int &c : cost)
        cin >> c;

    vector<pair<int64_t, int>> sorted(N);

    for (int i = 0; i < N; i++) 
        sorted[i] = {chocolates[i] * cost[i], i};
    
    sort(chocolates.rbegin(), chocolates.rend());   // we can also use a heap

    int64_t answer = -1;

    for (int i = 0; i < N; i++) {
        int index = sorted[i].second;
        
        if (teddy >= chocolates[index]) {
            teddy -= chocolates[index];
            continue;
        }

        answer = max<int64_t>(answer, int64_t(chocolates[index] - teddy) * cost[index]);
        teddy = 0;
    }

    cout << answer << '\n';
}

/*
5 10
1 2 2 3 3
1 1 1 1 1

3 0
2 3 3
2 2 2
*/