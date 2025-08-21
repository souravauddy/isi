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

const int INF = int(1e9 + 5);

template<typename Type>
void clear(std::stack<Type> &stack) {
    while (!stack.empty())
        stack.pop();
}

int main(const int argc, const char **argv) {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int N = int(argc - 1);
    std::vector<int> numbers;
    std::vector<int> nearest_element_index(N, -1), nearest_difference(N, INF);
    std::stack<int> stack;

    for (int i = 1; i <= N; i++)
        numbers.push_back(std::stoi(argv[i]));

    auto check_nearest = [&](int index) -> void {
        int top;

        while (!stack.empty() && numbers[top = stack.top()] < numbers[index]) {
            int difference = std::abs(top - index);

            if (difference < nearest_difference[top]) {
                nearest_difference[top] = difference;
                nearest_element_index[top] = index;
            }

            stack.pop();
        }

        stack.push(index);
    };

    stack.push(0);

    for (int i = 1; i < N; i++)
        check_nearest(i);

    clear(stack);
    stack.push(N - 1);

    for (int i = N - 2; i >= 0; i--)
        check_nearest(i);

    for (int i = 0; i < N; i++)
        std::cout << '(' << numbers[i] << ", " << (~nearest_element_index[i] ? numbers[nearest_element_index[i]] : -1) << ')' << " \n"[i + 1 == N];
}
