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

const int MIN_DIGIT = int('0');

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif

    int P, Q, position = -1;
    std::string decimal_expansion;
    std::cin >> P >> Q;

    assert(Q > 0);

    decimal_expansion.append(std::to_string(P / Q));
    int remainder = P % Q, index = 0;

    if (remainder)
        decimal_expansion.push_back('.');

    std::vector<int> intermediate_quotients;
    std::unordered_map<int, int> remainders;
    remainders[remainder] = index++;
    P = remainder;
    
    while (remainder > 0) {
        P = P * 10;

        while (P < Q) {
            P = P * 10;
            intermediate_quotients.push_back(0);
        }

        intermediate_quotients.push_back(P / Q);
        remainder = P % Q;

        if (remainders.contains(remainder)) {
            position = remainders.at(remainder);
            break;
        }

        remainders[remainder] = index++;
        P = remainder;
    }

    for (int i = 0; i < intermediate_quotients.size(); i++) {
        if (i == position)
            decimal_expansion.push_back('(');

        decimal_expansion.push_back(intermediate_quotients[i] + MIN_DIGIT);
    }

    if (~position)
        decimal_expansion.push_back(')');

    std::cout << decimal_expansion << '\n';
}
