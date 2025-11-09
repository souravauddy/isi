#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <print>

struct union_find {  // union find using rank and path compression, only valid for un-directed graphs
    std::vector<int> parent, rank;
    int components = 0;

    union_find(int size) {
        parent.assign(size + 1, 0);
        rank.assign(size + 1, 1);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int vertex) {
        if (parent[vertex] == vertex)
            return vertex;
        return parent[vertex] = find(parent[vertex]);
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);

        if (a == b) 
            return false;

        if (rank[a] < rank[b])
            std::swap(a, b);

        parent[b] = parent[a];
        rank[a] += rank[b];
        components++;

        return true;
    }
};

int main() {
    int vertices, edges;
    std::cin >> vertices >> edges;
    std::vector<std::array<int, 2>> edge_list(edges);

    for (int e = 0; e < edges; e++)
        std::cin >> edge_list[e][0] >> edge_list[e][1];
    
    union_find UF(vertices);

    for (const auto &edge : edge_list) {
        if (UF.unite(edge[0], edge[1]) == false) {
            std::println("Cycle is Present in the graph.");
            return 0;
        }
    }

    std::println("Cycle not present");
}