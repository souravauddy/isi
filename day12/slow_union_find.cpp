#include <iostream>
#include <vector>
#include <numeric>

struct slow_union_find {
    std::vector<int> parent;
    int components = 0;

    slow_union_find(int capacity) {
        parent.assign(capacity + 1, 0);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);

        if (x == y)
            return false;

        for (int i = 0; i < int(parent.size()); i++)
            if (parent[i] == y)
                parent[i] = x;

        return true;
    }
};