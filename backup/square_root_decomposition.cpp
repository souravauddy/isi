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

constexpr static const int INF = int(1e9 + 5);

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

    const int BLOCK_SIZE = int(sqrt(N));

    std::vector<int> blocks(N / BLOCK_SIZE + 1, -INF);
    int block_index = -1;

    for (int i = 0; i < N; i++) {
        block_index += i % BLOCK_SIZE == 0;
        blocks[block_index] = std::max(blocks[block_index], numbers[i]);
    }

    auto update = [&](int index, int value) -> bool {
        numbers[index] = value;
        int block_index = index / BLOCK_SIZE;
        blocks[block_index] = std::max(blocks[block_index], value);
        return true;
    };

    auto query = [&](int left, int right) -> int {
        assert(left <= right && left >= 0 && right < N);

        int left_block_number = left / BLOCK_SIZE, right_block_number = right / BLOCK_SIZE;
        int difference = right_block_number - left_block_number - 1, answer = -INF;

        while (difference-- > 0)
            answer = std::max(answer, blocks[++left_block_number]);

        for (int bound = left; bound % BLOCK_SIZE && bound <= right; bound++)
            answer = std::max(answer, numbers[bound]);

        for (int bound = std::max(BLOCK_SIZE * right_block_number, left); bound <= right && bound < N; bound++)
            answer = std::max(answer, numbers[bound]);

        return answer;
    };

    int queries;
    std::cin >> queries;
    
    for (int qry = 0; qry < queries; qry++) {
        int type;
        std::cin >> type;

        switch(type) {
            case 0:
                int left, right;
                std::cin >> left >> right;
                std::cout << query(left, right) << '\n';
                break;
            case 1:
                int index, value;
                std::cin >> index >> value;
                update(index, value);
                break;
            default:
                assert(false);
        }
    }
}
