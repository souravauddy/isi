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

void run_case() {
    int N;
    cin >> N;
    vector<int> A(N);

    bool negative_present = false;
    bool all_negative = true;

    [](int a, int b) -> int {
        return a * b; 
    }(2, 4);

    for (int &a : A) {
        cin >> a;
        
        if (a < 0)
            negative_present = true;
        if (a >= 0)
            all_negative = false;
    }

    vector<int> &numbers = A;

    int64_t Min = *min_element(numbers.begin(), numbers.end());
    int64_t Max = *max_element(numbers.begin(), numbers.end());
    int64_t max_answer = Max, min_answer = Min;

    if (negative_present) {
        max_answer = max(Max * Max, Min * Min);
        min_answer = Max * (all_negative ? Max : Min);
    } else {
        max_answer = Max * Max;
        min_answer = Min * Min;
    }

    cout << min_answer << ' ' << max_answer << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    vector<vector<int>> adjacency_list(1e5 + 5);

    int tests;
    cin >> tests;

    for (int i = 0; i < 200; i++)
        cout << i << '\n';
    cout << '\n';

    while (tests-- > 0) {
        run_case();
    }
}