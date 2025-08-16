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

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

const int MOD = int(1e9 + 7);
const int ROOT = 0;

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int vertices, edges;
    cin >> vertices >> edges;
    vector<int> A(vertices);
    vector<vector<int>> adjacency_list(vertices);
    vector<int> subtree_sum(vertices);
    vector<int> parent(vertices, -1);
    vector<bool> visited(vertices, false);

    for (int &a : A)
        cin >> a;

    for (int e = 0; e < edges; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    auto Dfs = y_combinator([&](auto dfs, int vertex, int parent_) -> int {
        debug(vertex);
        visited[vertex] = true;
        
        for (auto node : adjacency_list[vertex])
            if (!visited[node])
                subtree_sum[vertex] += dfs(node, vertex);

        parent[vertex] = parent_;
        subtree_sum[vertex] += A[vertex];
        return subtree_sum[vertex];
    });

    Dfs(ROOT, -1);

    // debug(adjacency_list[0].size());

    int answer = 0;

    // assert(count(visited.begin(), visited.end(), true) == vertices);
    // output_vector(subtree_sum);
    // output_vector(parent);

    auto get_value = [&](const vector<int> &edge) -> int {
        int child_sum = subtree_sum[edge[1]];
        int parent_sum = parent[edge[0]] != -1 ? subtree_sum[parent[edge[0]]] : 0;
        parent_sum -= child_sum;
        return (1LL * child_sum * parent_sum) % MOD;
    };

    for (int vertex = 0; vertex < vertices; vertex++)
        for (auto node : adjacency_list[vertex]) {
            answer = max({answer, get_value({vertex, node}), get_value({node, vertex})});
        }

    cout << answer << '\n';
}

/*
4 3
10 5 12 6
1 2
1 4
4 3

13 12
42 468 335 501 170 725 479 359 963 465 706 146 282
10 6
3 2
12 7
9 5
2 1
8 3
7 1
4 2
6 3
11 4
5 3
13 11

10 

*/