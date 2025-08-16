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

map<char, int> INTEGER = {{'R', 4}, {'Y', 2}, {'B', 1}, {'O', 6}, {'P', 5}, {'G', 3}, {'A', 7}, {'U', 0}};

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cerr << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int power_of_2(int number) {
    return __builtin_popcount(number) == 1;
}

int rightmost_set_bit(size_t number) {
    int position = 0;

    while (number > 0 && (number & 1) == 0) {
        position++;
        number >>= 1;
    }

    return number == 0 ? 32 : position;
}

void run_case(int test_case) {
    int N;
    string painting;
    cin >> N >> painting;
    vector<int> colours(N);
    int cost = 0;

    for (int i = 0; i < N; i++) 
        colours[i] = INTEGER[painting[i]];

    for (int i = 0; i < N; i++) {
        while (colours[i] > 0) {
            int bit = __builtin_ctz(colours[i]), j = i;
            int offset = ~(1 << bit);
            cost++;

            while (j < N && colours[j] & (1 << bit)) {
                colours[j] &= offset;
                j++;
            }
        }

        assert(colours[i] == 0);
    }

    cout << "Case #" << test_case << ": " << cost << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;
    
    for (int test = 0; test < tests; test++) {
        run_case(test + 1);
    }
}