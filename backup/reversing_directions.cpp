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
#include <queue>
#include <stack>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <memory>

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
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

std::array<std::string, 2> decompose(std::string &line) {
    std::stringstream in(line);
    std::array<std::string, 2> decomposition;
    std::string word;

    in >> decomposition[0];

    while (in >> word)
        decomposition[1].append(word + " ");
    
    if (!decomposition[1].empty())
        decomposition[1].pop_back();

    return decomposition;
}

void run_case() {
    std::string string_N;
    std::getline(std::cin, string_N);
    int N = std::stoi(string_N);

    std::vector<std::array<std::string, 2>> decomposition, reverse_decomposition;

    for (int i = 0; i < N; i++) {
        std::string line;
        std::getline(std::cin, line);
        auto intermediate = decompose(line);
        decomposition.push_back(intermediate);
        reverse_decomposition.push_back(intermediate);
    }

    std::reverse(reverse_decomposition.begin(), reverse_decomposition.end());

    reverse_decomposition[0][0] = "Begin";

    for (int i = 1, j = N - 1; i < N; i++, j--) {
        if (decomposition[i][0] == "Right") {
            reverse_decomposition[j][0] = "Left";
        } else {
            reverse_decomposition[j][0] = "Right";
        }
    }

    for (int i = 0; i < N; i++)
        std::cout << reverse_decomposition[i][0] + " " + reverse_decomposition[i][1] << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif

    std::string string_tests;
    std::getline(std::cin, string_tests);
    int tests = std::stoi(string_tests);

    while (tests-- > 0) {
        run_case();
    }
}
