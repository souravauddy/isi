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
        os << other[i] << ' ';
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" nodehesis

const int INF = int(1e9 + 5);

struct segment {
    int low, high;
    int sum;

    segment(int _sum = 0, int _low = 0, int _high = 0) {
        sum = _sum;
        low = _low;
        high = _high;
    }

    friend ostream& operator<<(ostream &os, const segment &other) {
        return os << "{" << other.low << ", " << other.high << ", " << other.sum << "}";
    }

    friend istream& operator>>(istream &in, segment &other) {
        return in >> other.low >> other.high >> other.sum;
    }
};

struct SegmentTree {    // not the most efficeint implementation of the segment tree, try to write an iterative one, and not a recursive one. this is the main idea.
    int tree_size, size;
    vector<segment> tree;
    const int ROOT = 1;
    
    // add more variables as required

    SegmentTree(int _size = 0) : size(_size) {}

    void build(const vector<int> &initial) {
        tree.resize(4 * size + 1);
        tree_size = 4 * size + 1;
        int initial_index = 0;

        y_combinator([&](auto self, int index, int low, int high) -> int {
            assert(index <= tree_size);
            tree[index].low = low;
            tree[index].high = high;

            if (low == high) {
                tree[index].sum = initial[initial_index];
                return initial[initial_index++];
            }

            int mid = low + (high - low) / 2;
            int low_sum = self(2 * index, low, mid);      
            int high_sum = self(2 * index + 1, mid + 1, high);     
            int sum = low_sum + high_sum;

            tree[index].sum = sum;
            return sum;
        })(ROOT, 0, size - 1);
    }

    void update(int index, int value) {
        y_combinator([&](auto self, int node) -> int {
            if (tree[node].low == tree[node].high && tree[node].high == index) {
                int difference = value - tree[node].sum;
                tree[node].sum = value;
                return difference;
            }

            int mid = tree[node].low + (tree[node].high - tree[node].low) / 2;
            int difference = self(2 * node + index > mid);
            tree[node].sum += difference;
            return difference;
        })(ROOT);
    }

    size_t query(int low, int high) {
        return y_combinator([&](auto self, int node) -> int {
            if (tree[node].low >= low && tree[node].high <= high) 
                return tree[node].sum;
            
            if (tree[node].low > high || tree[node].high < low) // lies completely out
                return 0;

            return tree[node].sum = self(2 * node) + self(2 * node + 1);
        })(ROOT);
    }
};

int main() {
    int N;
    cin >> N;
    vector<int> numbers(N);
    int64_t sum = 0;

    for (int &number : numbers)
        number = rand() % 20;

    SegmentTree tree(N);
    tree.build(numbers);
}