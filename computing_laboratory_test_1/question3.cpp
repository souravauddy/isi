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

struct function {
    int co_ordinates_length;
    std::vector<std::array<int, 2>> points;

    function() = default;

    function(int co_ordinates_length) noexcept {
        this->co_ordinates_length = co_ordinates_length;
        this->points.assign(co_ordinates_length, {0, 0});
    }

    function(std::string &string_function) noexcept {
        std::stringstream in(string_function);
        std::string string_co_ordinates;

        in >> string_co_ordinates;
        this->co_ordinates_length = std::stoi(string_co_ordinates);

        for (int l = 0; l < this->co_ordinates_length; l++) {
            std::array<std::string, 2> point;
            in >> point[0] >> point[1];
            this->points.emplace_back(std::stoi(point[0]), std::stoi(point[1]));
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    std::string string_function_f, string_function_g, string_interval;
    std::getline(std::cin, string_function_f);
    std::getline(std::cin, string_function_g);

    function function_f(string_function_f), function_g(string_function_g);
    std::array<int, 2> interval;
    std::cin >> interval[0] >> interval[1];

    
}
