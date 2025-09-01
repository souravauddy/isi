#include "binary_trees.h"
#include <iostream>
#include <vector>

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

void read(BINARY_TREE *tree) {
    for (int node = 0; node < tree->capacity; node++) {
        int left, right;
        std::cin >> left >> right;

        tree->nodes[node].left = left;
        tree->nodes[node].right = right;

        if (left != INT_NULL)
            tree->nodes[left].parent = node;

        if (right != INT_NULL)
            tree->nodes[right].parent = node;
    }
}

int main() {
    int capacity;
    std::cin >> capacity;
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));

    init_tree(tree, capacity);
    read(tree);

    auto member_node = [&](int node) -> bool {
        assert(node != INT_NULL);
        return  !(tree->nodes[node].left != INT_NULL && tree->nodes[node].right != INT_NULL);
    };

    auto preorder = y_combinator([&](auto self, int node) -> int {
        if (node == INT_NULL)
            return 0;

        std::cout << node << ' ';
        return member_node(node) + self(tree->nodes[node].left) + self(tree->nodes[node].right);
    });

    for (int node = 0; node < tree->capacity; node++) {
        if (tree->nodes[node].parent == INT_NULL) {
            std::cout << preorder(node) << '\n';
        }
    }

    free_tree(tree);
}
