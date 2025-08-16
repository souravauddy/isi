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
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

const int INF = int(1e9 + 5);

void run_case() {
    int N;
    std::cin >> N;
    std::vector<std::array<int, 2>> matrix;
    int64_t answer = 0;

    for (int i = 0; i < N; i++) {
        int size;
        std::cin >> size;
        std::vector<int> row(size);

        for (auto &element : row)
            std::cin >> element;

        std::sort(row.begin(), row.end());

        matrix.push_back({row[0], row[1]});
    }

    int second_minimum = INF, second_min_index = -1, minimum = INF;

    for (int i = 0; i < matrix.size(); i++) {
        if (second_minimum > matrix[i][1]) {
            second_min_index = i;
            second_minimum = matrix[i][1];
        }

        minimum = std::min<int>({minimum, matrix[i][0]});
    }

    assert(second_min_index != -1);
    answer += minimum;

    for (int i = 0; i < matrix.size(); i++) {
        if (i != second_min_index) {
            answer += matrix[i][1];
        }
    }

    std::cout << answer << std::endl;
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

/*

220 40

50 100 20

20 49 29 4920 9402

220 + 50 + 20

290


*/