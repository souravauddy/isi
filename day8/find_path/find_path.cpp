#include "../binary_trees.h"
#include <iostream>

bool find_path(BINARY_TREE *tree, int node, int target, int sum = 0) {
    if (target == sum && node == INT_NULL)
        return true;

    if (node == INT_NULL)
        return false;

    return find_path(tree, tree->nodes[node].left, target, sum + tree->nodes[node].data) ||
                find_path(tree, tree->nodes[node].right, target, sum + tree->nodes[node].data);
}

int main() {
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));
    assert(tree);

    int capacity;
    std::cin >> capacity;

    init_tree(tree, capacity);
    read_tree(tree);

    int target;
    std::cin >> target;

    tree->root = 0;

    std::cout << find_path(tree, tree->root, target) << '\n';

    free_tree(tree);
}
