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

const int INF = int(1e9 + 5);

struct segment_tree {
    constexpr static const int ROOT = int(1);
    std::vector<int> tree;
    size_t tree_size, size;

    segment_tree() = default;

    [[nodiscard]]
    size_t nearest_power_of_2(int number) const {
        return 1 << (32 - __builtin_clz(number));
    }

    void update(int index, int value) noexcept {
        size_t tree_index = nearest_power_of_2(size);

        tree_index = tree_index - 1 + index;

        while (tree_index > 0) {
            tree[tree_index] = std::min(tree[tree_index], value);
            tree_index /= 2;
        }
    }

    [[nodiscard]]
    int query(int start, int end) const {
        return y_combinator([&](auto self, int node, int left, int right) -> int {
            if (end < left || start > right)
                return INF;
            
            if (left >= start && right <= end) {
                return tree[node];
            }

            int mid = left + (right - left) / 2;

            return std::min(self(2 * node, left, mid), self(2 * node + 1, mid + 1, right));
        })(ROOT, 0, nearest_power_of_2(size) - 1);
    }

    [[nodiscard]]
    int query(int index) const {
        int tree_index = nearest_power_of_2(size);
        tree_index = tree_index - 1 + index;

        return tree[tree_index];
    }

    void build(const std::vector<int> &initial) noexcept {
        size = initial.size();
        tree_size = nearest_power_of_2(size);
        tree.assign(tree_size * 2, INF);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int N;
    std::cin >> N;
    std::vector<int> locations(N);

    for (int &location : locations)
        std::cin >> location;

    segment_tree tree;
    tree.build(locations);

    tree.update(0, 0);

    for (int i = 0; i < N; i++) {
        int reach = std::min(i + locations[i], N - 1);
        int cost = std::min(tree.query(i + 1, N - 1) + 1, tree.query(i) + 1);
        tree.update(reach, cost);
    }

    std::cout << tree.query(N - 1) << '\n';
}
