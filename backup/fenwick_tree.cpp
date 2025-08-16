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
    cerr << endl;
}

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
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
    cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

struct fenwick_tree {
    int tree_size;
    vector<int> prefix_sum_tree;

    fenwick_tree(int size) {
        tree_size = size + 1;
        prefix_sum_tree.assign(tree_size, 0);
    }

    void build(const vector<int> &numbers) {
        for (int i = 1; i <= tree_size; i++) {
            prefix_sum_tree[i] += numbers[i - 1];

            if (i + (i & -i) <= tree_size)
                prefix_sum_tree[parent(i)] += prefix_sum_tree[i]; 
        }
    }

    int parent(int index) {
        return index + (index & -index);
    }

    void update(int index, int value) {
        int index_value = get_result(index + 1) - get_result(index);
        int diff = value - index_value;
        debug(index_value);

        for (int i = index + 1; i <= tree_size; i = parent(i))
            prefix_sum_tree[i] += diff;
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

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int N;
    cin >> N;
    vector<int> numbers(N);

    for (int &number : numbers)
        cin >> number;

    fenwick_tree tree(N);
    tree.build(numbers);

}


/*
how does point update work?

I understand update the node, and then update the parents, updating the node is simple just change it, finding the parents is challenging.

8 1000       |
7 0111 |     |
6 0110   |   |
5 0101 | |   | 5
4 0100     | | 10
3 0011 |   | | 3
2 0010   | | | 3
1 0001 | | | | 1
*/