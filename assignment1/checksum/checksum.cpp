#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <sstream>
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

constexpr const int MOD = int(11);
constexpr const char DIGIT = char('0');

std::string ISBN_formatted(const std::string &number) noexcept {
    std::string formatted;
    formatted.reserve(13);
    int insertion_position = 1, jump = 1;

    for (int i = 0; i < number.size(); i++) {
        if (i == insertion_position) {
            formatted.push_back('-');
            jump += 2;
            insertion_position += jump;
        }

        formatted.push_back(number[i]);
    }

    return formatted;
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    std::string number;
    std::cin >> number;
    assert(number.size() == 9);

    int checksum = 0, co_efficient = 10;

    for (int i = 0; i < number.size(); i++) {
        checksum += (number[i] - DIGIT) * co_efficient;
        co_efficient--;
    }

    std::cout << checksum << '\n';

    checksum %= MOD;
    //assert(checksum < 10); // 10 is not a valid checksum for ISBN-10
    number.push_back(DIGIT + checksum % MOD);

    std::cout << ISBN_formatted(number) << '\n';
}

/*
0 2 0 1 3 1 4 5 2
0 1 2 3 4 5 6 7 8
 -     -         - 5
*/
