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
#include <ranges>
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

enum child_type {
    left, right
};

constexpr static const int SENTINEL = int(1e9 + 5);
constexpr static const int ROOT = int(1);

inline int parent(int child) {
    return child / 2;
}

template<typename Type>
void output_vector(const std::vector<Type> &numbers, int start = -1, int end = -1, bool add_one = false) {
    if (start == -1)
        start = 0;
    if (end == -1)
        end = numbers.size();

    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

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

    std::vector<int> heap(N + 1, SENTINEL);

    for (int i = 0; i < N; i++)
        heap[i + 1] = numbers[i];

    for (int node = N; node >= ROOT; node--) {
        int parent_node = parent(node);

        if (heap[node] > heap[parent_node]) {
            std::swap(heap[node], heap[parent_node]);
            
            int current = node;

            while (2 * current <= N) {
                int child = 2 * current, maximum_value_child = child + (heap[child] < heap[child + 1]);

                if (heap[current] > heap[maximum_value_child])
                    break;

                std::swap(heap[current], heap[maximum_value_child]);
                current = maximum_value_child;
            }
        }        
    }

    std::make_heap(numbers.begin(), numbers.end());

    output_vector(numbers);
    output_vector(heap, 1);

    debug(std::is_heap(std::next(heap.begin()), heap.end()) ? "True" : "False");
}

// 
// 1979 186 1371 2216 4467 4830 4910 4056 2330 4829 3157 3201 1247 4021 67 2571 758 237 1261 1604