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

using std::cin, std::cout;
using std::string, std::vector;

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
        os << other[i] << ' ';
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    std::cerr << " [" << head << ']';
    debug_out(args...);
}

#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis
// Never use vector<bool>, during writing applications but you can use std::vector<bool> during competitions

struct check {
    int x;

    check() {
        std::cout << "copying" << '\n';
    }

    check(int _x) : x(_x) {
        std::cout << "copying" << '\n';
    }

    check(const check &other) : x(other.x) {
        std::cout << "copying copy constructor" << '\n';
    }

    check(const check &&other) : x(std::move(other.x)) {
        std::cout << "not copying" << '\n';
    }

    check operator=(const check &other) {
        x = other.x;
        return *this;
    }

    check operator=(const check &&other) {
        x = std::move(other.x);
        return *this;
    }

    check operator+(const check &other) const {
        check c;
        c.x = this->x + other.x;
        return c;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif

    check c{20};

    c + c = c;

    std::cout << c.x << '\n';
}

