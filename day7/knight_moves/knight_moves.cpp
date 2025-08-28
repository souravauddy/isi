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

const int MAX_MOVES = int(8);

template<typename Type>
void output_vector(const std::vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    const std::array<int, MAX_MOVES> KNIGHT_ROW_STEP = {2, 1, -1, -2, -2, -1, 1, 2}, KNIGHT_COLUMN_STEP = {1, 2, 2, 1, -1, -2, -2, -1};

    int M, N, row, column, steps;
    std::cin >> M >> N >> row >> column >> steps;
    std::vector<int> valid_steps(steps + 1);

    auto valid = [&](auto &&r, auto &&c) -> bool {
        return (r >= 0 && r < M && c >= 0 && c < N);
    };

    y_combinator([&](auto self, int row, int column, int step) -> void {
        if (step == steps + 1)
            return;

        valid_steps[step]++;

        for (int m = 0; m < MAX_MOVES; m++) {
            int next_row = row + KNIGHT_ROW_STEP[m], next_column = column + KNIGHT_COLUMN_STEP[m];

            if (valid(next_row, next_column))
                self(next_row, next_column, step + 1);
        }
    })(row, column, 0);

    int sample_space = 1;
    double probability = 1;

    for (int step = 1; step <= steps; step++) {
        probability *= (double) valid_steps[step] / (sample_space * MAX_MOVES);
        sample_space = valid_steps[step];
    }

    std::cout << std::fixed << std::setprecision(6) <<  probability << '\n';
}
