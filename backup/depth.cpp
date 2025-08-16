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

#ifdef LOCAL
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

struct mod_int {
    int a;

    mod_int(int _a = 5) : a(_a) {}

    mod_int& operator++() {
        a++;
        return *this;
    }

    friend ostream& operator<<(ostream &os, const mod_int &other) {
        return os << other.a;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    mod_int a;
    cout << ++a << '\n';

    int vertices, edges;
    cin >> vertices >> edges;
    vector<vector<int>> adjacency_list(vertices);
    vector<int> height(vertices);
    vector<int> depth(vertices);

    for (int e = 0; e < edges; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adjacency_list[u].push_back(v);
    }

    int root;
    cin >> root;

    y_combinator([&](auto dfs, int vertex, int vertex_depth) -> int {
        depth[vertex] = vertex_depth;

        if (adjacency_list[vertex].empty()) 
            return 1;

        for (int node : adjacency_list[vertex]) 
            height[vertex] = max(height[vertex], dfs(node, vertex_depth + 1));
        
        return ++height[vertex];      
    })(root, 0);    

    output_vector(height);
    output_vector(depth);
}

/*
Input:

13 12
1 2
1 3
1 13
2 5
3 4
5 6
5 7
5 8
8 12
4 9
4 10
10 11
0
*/