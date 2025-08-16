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
    std::cerr << endl;
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
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

constexpr uint64_t get_root(uint64_t number) {
    return uint64_t(round(sqrtl(number)));
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    uint64_t N = 1000000000;
    const uint64_t ROOT = get_root(N);
    vector<bool> sieve(ROOT + 1, true);
    vector<uint64_t> primes;
    sieve[0] = sieve[1] = false;

    for (uint64_t number = 2; number <= ROOT; number++)
        if (sieve[number]) {
            primes.push_back(number);
            
            for (uint64_t factor = number * number; factor <= ROOT; factor += number)
                sieve[factor] = false;
        }

    vector<int> rest_primes;
    const int BLOCK_SIZE = 100000;
    sieve.assign(BLOCK_SIZE + 1, true);

    for (uint64_t block = ROOT; block <= N; block += BLOCK_SIZE) { // O(N * sqrt(N) / ln(sqrt(n)))
        fill(sieve.begin(), sieve.end(), true);

        for (uint64_t prime : primes) {
            uint64_t first_factor = max(prime * prime, (block / prime) * prime);
            first_factor += first_factor < block ? prime : 0;
            assert(first_factor >= block);

            if (first_factor > block + BLOCK_SIZE)
                break;

            for (uint64_t factor = first_factor; factor <= block + BLOCK_SIZE; factor += prime) {
                assert(factor >= block);
                sieve[factor - block] = false;
            }
        }

        for (int r = 0; r <= BLOCK_SIZE; r++)
            if (sieve[r])
                rest_primes.push_back(block + r);
    }

    debug(primes.size());
    debug(rest_primes.size());
}