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
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <memory>

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
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

const uint64_t LIMIT = uint64_t(std::pow(10, 10));

bool prime(uint64_t number) {
    if (number == 2)
        return true;

    for (uint64_t factor = 2; factor * factor <= number; number++) {
        if (number % factor == 0)
            return false;

        return true;
    }

    return number >= 2;
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return __int128_t(a * b) / std::__gcd(a, b);
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif

    uint64_t N;
    std::cin >> N;
    std::vector<uint64_t> numbers(N);

    if (N == 0LL) {
        std::cout << "None" << '\n';
        return 0;
    }

    for (auto &number : numbers)
        std::cin >> number;

    numbers.push_back(N);

    std::sort(numbers.begin(), numbers.end());
    uint64_t least_common_multiple = numbers.back();

    for (uint64_t i = 1; i < N + 1; i++) {
        least_common_multiple = lcm(least_common_multiple, numbers[i]);

        if (least_common_multiple >= LIMIT) {
            std::cout << "None" << '\n';
            return 0;
        }
    }

    uint64_t goal = least_common_multiple + numbers[0];

    if (!prime(goal) || (((goal) % numbers[0]) == numbers[0]) || goal >= LIMIT) {
        std::cout << "None" << '\n';
        return 0;
    }

    std::cout << goal << '\n';
}
