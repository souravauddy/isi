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

struct UnionFind {  // union find using rank and path compression
    vector<int> parent;
    vector<int> rank;
    int components = 0;

    UnionFind(int size) {
        parent.assign(size + 1, 0);
        rank.assign(size + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int vertex) {
        if (parent[vertex] == vertex)
            return vertex;
        return parent[vertex] = find(parent[vertex]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) 
            return false;

        if (rank[a] < rank[b]) {
            parent[a] = parent[b];
            rank[b] += rank[a];
        } else {
            parent[b] = parent[a];
            rank[a] += rank[b];
        }

        components++;

        return true;
    }

    bool same_set(int a, int b) {
        return find(a) == find(b);
    }

    int count() {
        return parent.size() - components - 1;  // since we are taking +1 on the size we are doing -1
    }
};  

struct Edge {
    int source, weight, destination;

    Edge(int _source = 0, int _destination = 0, int _weight = 0) : source(_source), destination(_destination), weight(_weight) {}

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

int main() {
    int vertices, edges;
    cin >> vertices >> edges;
    vector<Edge> sorted_edges;
    vector<vector<int>> spanning_tree(vertices);

    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        sorted_edges.push_back({u, v, weight});
    }

    sort(sorted_edges.begin(), sorted_edges.end());

    UnionFind UF(edges);
    int64_t total_weight = 0;
    
    for (auto edge : sorted_edges) {
        if (UF.unite(edge.source, edge.destination)) {
            total_weight += edge.weight;
            spanning_tree[edge.source].push_back(edge.destination);
        }
    }

    for (int vertex = 0; vertex < vertices; vertex++)
        if (!spanning_tree[vertex].empty()) {
            cout << "For the source " << vertex << ": ";

            for (int edge : spanning_tree[vertex])
                cout << edge << ' ';
            cout << '\n';
        }

    debug(total_weight);
}

/*
4 5
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

*/