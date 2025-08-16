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

const char MIN_CHAR = char('a');
const int ALPHABET = int(26);

void run_case() {
    int N;
    string str;
    cin >> N >> str;

    if (N > 5) {
        cout << "NO" << '\n';
        return;
    }

    const string TIMUR = "Timur";
    map<char, int> timur, frequency;
    bool upper_T = false;

    for (int i = 0; i < N; i++) {
        if (str[i] != 'T') {
            if (str[i] >= 'a' && str[i] <= 'z') 
                continue;

            cout << "NO" << '\n';
            return;
        } else if (str[i] == 'T') {
            upper_T = true;
        }
    }

    for (char c : TIMUR)
        timur[c - MIN_CHAR]++;

    for (char c : str) 
        frequency[c - MIN_CHAR]++;

    cout << (upper_T && timur == frequency ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}