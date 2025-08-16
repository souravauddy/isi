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

const int INF = int(1e9 + 5);

int next_power_of_2(int value) {
    if ((value & (value - 1)) == 0)
        return value;
    return int(uint32_t(INT_MIN) >> (__builtin_clz(value) - 1));
}

struct segment {
    int left, right, maximum, to_subtract;

    segment(int _left = 0, int _right = 0, int _maximum = -INF, int _to_subtract = 0, bool _to_change = false) : left(_left), right(_right), maximum(_maximum), to_subtract(_to_subtract) {}
};

struct segment_tree {
    static const int ROOT = int(1);
    std::vector<segment> tree;
    std::vector<int> base;

    segment_tree(std::vector<int> &initial) : base(initial) {
        tree.resize(2 * next_power_of_2(initial.size()));
    }
    
    void build() {
        return y_combinator([&](auto self, int node, int left, int right, auto &&index) -> void {
            tree[node].left = left;
            tree[node].right = right;

            if (left == right) {        // we have reached a leaf node.
                tree[node].maximum = base[index++];
                return;
            }

            int mid = left + (right - left) / 2;
            self(2 * node, left, mid, index);
            self(2 * node | 1, mid + 1, right, index);
            tree[node].maximum = std::max(tree[2 * node].maximum, tree[2 * node | 1].maximum);
        })(ROOT, 0, base.size() - 1, 0);
    }

    void pushdown(int node) {
        tree[2 * node].maximum -= tree[node].to_subtract;
        tree[2 * node].to_subtract += tree[node].to_subtract;
        tree[2 * node | 1].maximum -= tree[node].to_subtract;
        tree[2 * node | 1].to_subtract += tree[node].to_subtract;
        tree[node].to_subtract = 0;
    }

    void update(int left, int right, int to_subtract) {
        return y_combinator([&](auto self, int node) -> void {
            if (tree[node].left >= left && tree[node].right <= right) {
                tree[node].maximum -= to_subtract;
                tree[node].to_subtract += to_subtract;
                return;
            }

            if (left > tree[node].right || right < tree[node].left)
                return;

            if (tree[node].to_subtract)
                pushdown(node);
            
            self(2 * node);
            self(2 * node | 1); 
            tree[node].maximum = std::max(tree[2 * node].maximum, tree[2 * node | 1].maximum);
        })(ROOT);
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

    segment_tree tree(numbers);
    tree.build();
}
