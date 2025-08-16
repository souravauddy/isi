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

const int64_t INF64 = int(1e18 + 5);

void run_case() {
    int N;
    std::cin >> N;
    std::vector<int> tasks(N);

    for (int &task : tasks)
        std::cin >> task;

    std::vector<int64_t> prefix_sums(N, 0), suffix_sums(N, 0);

    prefix_sums[0] = tasks.front();

    for (int i = 1; i < N; i++)
        prefix_sums[i] = prefix_sums[i - 1] + tasks[i];

    for (int i = N - 2; i >= 0; i--)
        suffix_sums[i] = suffix_sums[i + 1] + tasks[i + 1];

    int64_t minimum = prefix_sums[N - 1];

    for (int i = 0; i < N; i++)
        minimum = std::min<int64_t>(minimum, std::max<int64_t>(prefix_sums[i], suffix_sums[i]));
    
    std::cout << minimum << '\n';
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
