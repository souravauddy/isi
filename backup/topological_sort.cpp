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

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

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
    vector<vector<int>> adjacency_list(vertices);   
    vector<bool> visited(vertices, false);

    for (int e = 0; e < edges; e++) {
        int u, v;
        cin >> u >> v;
        adjacency_list[u].push_back(v);
    }

    vector<int> sorted_vertices(vertices);  // topologically sorted vertices
    int index = vertices - 1;

    auto Dfs = y_combinator([&](auto dfs, int node) -> void {
        visited[node] = true;

        for (auto vertex : adjacency_list[node])
            if (!visited[vertex]) 
                dfs(vertex);

        sorted_vertices[index] = node;
        index--;
    });

    auto get_vertex = [&](int node) {
        for (int v = node; v < vertices; v++)
            if (!visited[v])
                return v;

        assert(false);
    };

    int source = 0;

    while (index >= 0) {
        source = get_vertex(source);
        Dfs(source);
    }
    
    output_vector(sorted_vertices);
}

/*
6 6
5 2
5 0
4 0
4 1
2 3
3 1
*/