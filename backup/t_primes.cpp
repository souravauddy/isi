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
#include <stdio.h>
#include <cassert>

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

const int SIEVE_MAX = int(1e6 + 5);
const int64_t A_MAX = int64_t(1e12 + 5);

vector<bool> sieve(SIEVE_MAX, true);
vector<int> primes;

void T_prime(int64_t number) {
    auto perfect_square = [&](auto number) -> int64_t {
        int64_t root = sqrt(number);  

        return root * root == number ? root : -1;
    };

    if (number == 4) {
        cout << "YES" << '\n';
        return;
    }

    int64_t root = perfect_square(number);

    if (number % 2 == 0 || root == -1) {
        cout << "NO" << '\n';
        return;
    }

    int low = 0, high = primes.size() - 1;
    number = root;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (primes[mid] == number) {
            cout << "YES" << '\n';
            return;
        } else if (primes[mid] < number) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << "NO" << '\n';
}

constexpr void preprocess() {
    sieve[1] = false;

    for (int64_t number = 2; number <= SIEVE_MAX && number * number <= A_MAX; number++) 
        if (sieve[number]) {
            primes.push_back(number);

            for (int64_t factor = number + number; factor <= SIEVE_MAX; factor += number) 
                sieve[factor] = false;
        }
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    preprocess();

    int N;
    cin >> N;
    vector<int64_t> A(N);

    for (int64_t &a : A) {
        cin >> a;
        T_prime(a);
    } 
}