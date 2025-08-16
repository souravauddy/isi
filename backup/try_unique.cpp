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

void run_case() {
    int n;
    cin >> n;
    int limit = (int) pow(10, n);
    int answer = 0;

    debug(limit);

    auto is_power = [&](int number) -> bool {
        int count_zeros = 0;
        int count_ones = 0;
        int count_digits = 0;

        while (number > 0) {
            count_ones += number % 10 == 1;
            count_zeros += number % 10 == 0;
            number /= 10;
            count_digits++;
        }

        return count_zeros + count_ones == count_digits && count_ones == 1;
    };

    for (int number = 0; number <= limit; number++) {
        int another_number = number;
        set<int> seen;
        int count = 0;

        while (number > 0) {
            seen.insert(number % 10);
            number /= 10;
            count++;
        }

        if (!seen.empty() && count == seen.size()) {
            answer++;
        }

        number = another_number;

        if (is_power(number))
            debug(number, answer);
    }

    debug(limit, answer);
}

int main() {
    int tests = 1;

    while (tests-- > 0) {
        run_case();
    }
}

// 100