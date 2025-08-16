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

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

void run_case() {
    int N;
    cin >> N;
    vector<int> A(N);
    map<int, int> frequency;

    for (int &a : A) {
        cin >> a;
        frequency[a]++;
    }

    int cost = frequency.size();
    int i = N - 1;

    int last = A.back();
    int count = 0;

    for (int i = N - 1; i >= 0; i--) {
        if (A[i] == last) {
            count++;
            continue;
        }

        if (count == frequency[last]) {
            cost--;
            count = 0;
        } else if (count != frequency[last]) {
            break;
        }

        if (A[i] > last)
            break;

        last = A[i];
        count = 1;
    }

    if (count == frequency[last]) {
        cost--;
        // count = 0;
    }

    cout << cost << '\n';   
}

int main() {
    ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    int tests = 1;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}