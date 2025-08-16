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
#include <mutex>
#include <numeric>
#include <tuple>
#include <mutex>
#include <unistd.h>
#include <thread>

// using namespace std;

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

struct sieve {
private:
    std::vector<int> primes;

public:
    int limit;

    sieve(int _limit) : limit(_limit) {}

    void compute() noexcept {
        std::bitset<10000000000> prime_marker;
        prime_marker.flip();

        for (int64_t number = 2; number <= limit; number++) {
            if (prime_marker[number] == true) {
                primes.push_back(number);

                for (int64_t factor = number * number; factor <= limit; factor += number) {
                    prime_marker[factor] = false;
                }
            }
        }
    }

    std::vector<int> primes() {
        return this->primes;
    }
};

int main() {
    int N;
    std::cin >> N;
    std::vector<bool> numbers(N, true);
    std::vector<int> primes;

    for (int64_t i = 2; i < N; i++)
        if (numbers[i]) {
            primes.push_back(i);

            for (int64_t number = i * i; number <= N; number += i)
                numbers[number] = false;
        }

    sleep

    std::cout << primes.size() << ' ' << primes.back() << '\n';
}
