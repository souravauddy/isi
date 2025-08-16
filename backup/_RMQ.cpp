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

const int INF = int(1e9 + 5);

struct segment {    
    int left, right;
    int value;
    
    segment(int _value = INF, int _left = 0, int _right = 0) : value(_value), left(_left), right(_right) {}
};

struct SegmentTree {
    int tree_size;
    int size;
    vector<segment> tree;
    
    static const int ROOT = int(1);
    
    SegmentTree(int _size) {
        size = _size;
        tree_size = 4 * size + 1;
        tree.resize(tree_size);
    }
    
    void build(const vector<int> &initial) {
        int index = 0;
        
        y_combinator([&](auto self, int node, int left, int right) -> void {
            tree[node].left = left;
            tree[node].right = right;
            tree[node].value = initial[index++];
            
            if (left == right) 
                return;
                
            int mid = left + (right - left) / 2;
            
            self(2 * node, left, mid);
            self(2 * node + 1, mid + 1, right);
        })(ROOT, 0, size - 1);
    }
    
    void update(int index, int value) {
        y_combinator([&](auto self, int node) -> void {
            if (tree[node].left == tree[node].right) {
                tree[node].value &= value;
                return;
            }
            
            int mid = tree[node].left + (tree[node].right - tree[node].left) / 2;

            self(2 * node + node > mid);            
            tree[node].value = min(tree[2 * node].value, tree[2 * node].value);
        })(ROOT);
    }
    
    int query(int left, int right) {
        return y_combinator([&](auto self, int node) -> int {
            if (tree[node].left > right || tree[node].right < left)
                return INF;
                
            if (tree[node].left >= left && tree[node].right <= right)
                return tree[node].value;
            
            return min(self(2 * node), self(2 * node + 1));
        })(ROOT);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
	int N, Q;
	cin >> N >> Q;
	vector<int> numbers(N);
	
	for (int &number : numbers)
	    cin >> number;
	    
    SegmentTree tree(N);
    tree.build(numbers);
    
    for (int q = 0; q < Q; q++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int index, X;
            cin >> index >> X;
            tree.update(index, X);
        } else {
            int left, right;
            cin >> left >> right;
            cout << tree.query(left, right) << '\n';
        }
    }
    
	return 0;
}
