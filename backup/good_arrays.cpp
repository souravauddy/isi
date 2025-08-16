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
#include <climits>
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
    std::cerr << std::endl;
}

template<typename Type>
std::ostream& operator<<(std::ostream &os, const std::vector<Type> &other) {
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
    std::cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

void run_case() {
    int N;
    std::cin >> N;
    std::vector<int> numbers(N);
    int64_t sum = 0;

    for (int &number : numbers) {
        std::cin >> number;
        sum += number;
    }

    for (int i = 0; i < N - 1; i++) {
        if (sum <= 0) {
            std::cout << "NO" << '\n';
            return;
        }

        if (numbers[i] > 1) {
            sum -= 1;
        } else {
            sum -= 2;
        }
    }

    if (N > 1 && sum == numbers.back()) {
        if (numbers.back() == 1) {
            std::cout << "NO" << '\n';
            return;
        }

        for (int i = N - 2; i >= 0; i--) {
            if (numbers[i] + 1 != numbers[i]) {
                std::cout << "YES" << '\n';
                return;
            }
        }

        std::cout << "NO" << '\n';
    } else if (sum > 0) {
        sum = 0;
    } else {
        std::cout << "NO" << '\n';
        return;
    }

    std::cout << (N > 1 && sum == 0 ? "YES" : "NO") << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif

    int tests;
    std::cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}

/*

1 1 1 1 2
1 1 1 4
2 2 2 1

40 40
38 42

2 2 2 4
3 3 3 1

2 2 2 5
2 2 1 1

2 1 2
1 3 1

5

2 * 2

1 1 2

1 1 1 2

1 1 3
2 2 1

3 3 3 3
2 2 2 6



1 2 1 2 2


5 5 5 5
6 6 6 2
*/