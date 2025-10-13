#include <iostream>
#include <numeric>
#include <vector>
#include <print>
#include <climits>

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
    int N;
    std::cin >> N;
    std::vector<int> numbers1(N), numbers2(N);

    for (int &number : numbers1)
        std::cin >> number;

    for (int &number : numbers2)
        std::cin >> number;

    union_find UF(N + 1);
    int operations = 0;

    for (int i = 1; i <= N; i++)
        operations += UF.unite(numbers1[i], numbers2[i]);
    
    std::println("{}", operations);
}