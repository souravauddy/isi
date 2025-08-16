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
#include <limits>
#include <bit>
#include <atomic>

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

const int ALPHABET = int(26);
const char MIN_CHAR = char('a');

void run_case() {
    int N, M;
    string smaller, larger;
    cin >> N >> M >> smaller >> larger;

    if (M < N) {
        string store = smaller;
        smaller = larger;
        larger = store;
    }
    
    vector<int> smaller_frequency(ALPHABET), larger_frequency(ALPHABET);

    for (char character : smaller)
        smaller_frequency[character - MIN_CHAR]++;

    for (char character : larger)
        larger_frequency[character - MIN_CHAR]++;

    for (int i = 0; i < ALPHABET; i++) {
        if (smaller_frequency[i] == 0) {
            int store = smaller_frequency[i];
            smaller_frequency[i] = max(smaller_frequency[i] - larger_frequency[i], 0);
            larger_frequency[i] = larger_frequency[i] - store;
        }
    }

    for (int i = 0; i < ALPHABET; i++)
        if (smaller_frequency[i] > 0 || larger_frequency[i] < 0) {   // no extra character in the smaller string
            cout << "NO" << '\n';
            return;
        }

    int count = 0;

    for (int i = 0; i < ALPHABET; i++)
        count += larger_frequency[i] % 2;

    cout << (count <= 1 ? "YES" : "NO") << '\n';
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