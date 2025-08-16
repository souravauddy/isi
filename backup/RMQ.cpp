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
    const int SIZE = other.size();
    if (SIZE <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < SIZE - 1; i++) 
        os << other[i] << ", ";
    return os << other[SIZE - 1] << ']';
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

template<typename Type>
void output_matrix(const std::vector<std::vector<Type>> &matrix, const int start = 0) {
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = start; i < row; i++) 
        for (int j = start; j < column; j++) 
            std::cout << std::setw(4) << (matrix[i][j]) << " \n"[j + 1 == column];
}

enum mode {
    MIN_MODE,
    MAX_MODE,
    GCD_MODE,
};

template<size_t MODE = MIN_MODE, typename Type = int>
struct range_query {
    std::vector<std::vector<Type>> table;
    std::vector<size_t> powers;

    constexpr range_query() = default;

    [[nodiscard]]
    constexpr static Type required(Type a, Type b) {
        if (MODE == MIN_MODE)
            return std::min(a, b);
        if (MODE == MAX_MODE)
            return std::max(a, b);
        if (MODE == GCD_MODE)
            return std::__gcd<size_t>(a, b);

        assert(false);
    }

    void build(const std::vector<Type> &numbers) noexcept {
        const int SIZE = numbers.size(), LOG = 32 - __builtin_clz(SIZE);

        powers.assign(SIZE, 0);
        table.assign(LOG, std::vector<int>(SIZE, -1));

        for (int i = 1; i < SIZE; i++)
            powers[i] = 31 - __builtin_clz(i);
        
        table[0] = numbers;

        for (int i = 1; i < LOG; i++)
            for (int j = 0; j + (1 << (i - 1)) < SIZE; j++)
                table[i][j] = required(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
    }

    [[nodiscard]]
    Type query(int left, int right) const {
        int power = powers[right - left];
        return required(table[power][left], table[power][1 + right - (1 << power)]);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif    

    int N;
    std::cin >> N;
    std::vector<int> numbers(N);

    for (int &number : numbers)
        std::cin >> number;

    range_query<MAX_MODE> RMQ;
    range_query<GCD_MODE> RGQ;

    RGQ.build(numbers);
    RMQ.build(numbers);

    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            debug(i, j, RMQ.query(i, j), RGQ.query(i, j));
}
