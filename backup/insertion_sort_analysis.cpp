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
#include <limits>
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

struct block {
    std::map<int, int> frequency;
    int count;

    block() = default;

    [[nodiscard]]
    int get_count() const {
        return count;
    }

    [[nodiscard]]
    int size() const {
        return int(frequency.size());
    }

    void update(const int element, const int value = 1) noexcept {
        frequency[element] += value;
        count++;
    }

    void insert(const int element) noexcept {
        frequency[element] = 0;
    }

    [[nodiscard]]
    int representative() const {
        assert(!frequency.empty());
        return int(std::prev(frequency.end())->first);
    }

    [[nodiscard]]
    int query(int element) const {
        int answer = 0;

        for (auto iterator = std::next(frequency.find(element)); iterator != frequency.end(); iterator++)
            answer += iterator->second;

        return answer;
    }
};

struct fenwick_tree {
    int tree_size;
    std::vector<int> prefix_sum_tree;

    fenwick_tree(int size) {
        tree_size = size + 1;
        prefix_sum_tree.assign(tree_size, 0);
    }

    void build(const std::vector<int> &numbers) {
        // for (int i = 1; i <= tree_size; i++) {
        //     prefix_sum_tree[i] += numbers[i - 1];

        //     if (i + (i & -i) <= tree_size)
        //         prefix_sum_tree[parent(i)] += prefix_sum_tree[i]; 
        // }
    }

    int parent(int index) {
        return index + (index & -index);
    }

    void update(int index, int value) {
        // int index_value = get_result(index + 1) - get_result(index);
        // int diff = value - index_value;

        // for (int i = index + 1; i <= tree_size; i = parent(i))
        //     prefix_sum_tree[i] += diff;
        prefix_sum_tree[index] += 1;
    }

    int query(int low, int high) {
        return get_result(high + 1) - get_result(low);
    }

    int get_result(int index) {
        int result = 0;

        for (int i = index; i > 0; i -= i & -i)
            result += prefix_sum_tree[i];

        return result;
    }
};

struct segment_tree {
    constexpr static const int ROOT = int(1);
    std::vector<int> tree;
    int size;

    segment_tree() = default;

    segment_tree(int _size) : size(_size) {
        tree.assign(2 * nearest_power_of_2(size), 0);
    }

    void build(const std::vector<int> &numbers) {
        // do nothing
    }

    void update(int index) {
        int tree_index = nearest_power_of_2(size) + index;
        
        while (tree_index > 0) {
            tree[tree_index] += 1;
            tree_index /= 2;
        }
    }

    [[nodiscard]]
    int64_t query(int left, int right = -1) const {
        right = size;

        return y_combinator([&](auto self, int node, int low, int high) -> int64_t {
            if (low >= left && high <= right)
                return tree[node];

            if (low > right || high < left)
                return 0;

            int mid = low + (high - low) / 2;
            return self(2 * node, low, mid) + self(2 * node + 1, mid + 1, high);
        })(ROOT, 0, nearest_power_of_2(size) - 1);
    }

    int nearest_power_of_2(int number) const {
        int result = 1;

        while (result <= number)
            result *= 2;

        return result;
    }
};

void run_case() {
    int N;
    std::cin >> N;
    std::vector<int> numbers(N);

    for (int &number : numbers)
        std::cin >> number;

    // std::set<int> sorted(numbers.begin(), numbers.end());
    // const int BLOCK_SIZE = int(sqrt(sorted.size()));
    // std::vector<block> blocks(sorted.size() / BLOCK_SIZE + 1);
    // std::unordered_map<int, int> index_finder;
    // int block_index = 0;

    // for (int element : sorted) {
    //     block_index += blocks[block_index].size() == BLOCK_SIZE;
    //     index_finder[element] = block_index;
    //     blocks[block_index].insert(element);
    // }

    // int64_t answer = 0;

    // auto query = [&](int element) -> int64_t {
    //     int answer = 0;
    //     int index = index_finder.at(element);
    //     blocks[index].update(element);
    //     answer += blocks[index].query(element);

    //     while (index + 1 < blocks.size())
    //         answer += blocks[++index].get_count();
        
    //     return answer;
    // };

    // for (int i = 0; i < N; i++)
    //     answer += query(numbers[i]);

    std::vector<int> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

    std::map<int, int> index;

    for (int i = 0; i < sorted.size(); i++)
        index[sorted[i]] = i;

    segment_tree tree(sorted.size());
    tree.build(sorted);

    int64_t answer = 0;

    for (int i = 0; i < N; i++) {
        tree.update(index.at(numbers[i]));
        answer += tree.query(index.at(numbers[i]) + 1);
    }

    std::cout << answer << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int tests;
    std::cin >> tests;

    while (tests-- > 0)
        run_case();
}
