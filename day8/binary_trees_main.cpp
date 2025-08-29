#include "binary_trees.h"
#include <iostream>
#include <vector>

void inorder(BINARY_TREE *tree, int root) {
    if (root == INT_NULL)
        return;

    inorder(tree, tree->nodes[root].left);
    std::cout << tree->nodes[root].data << ' ';
    inorder(tree, tree->nodes[root].right);
}

void post_order(BINARY_TREE *tree, int root) {
    if (root == INT_NULL)
        return;

    post_order(tree, tree->nodes[root].left);
    post_order(tree, tree->nodes[root].right);
    std::cout << tree->nodes[root].data << ' ';
}

int main(const int argc, const char **argv) {
    int capacity;
    std::cin >> capacity;
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));

    init_tree(tree, capacity);
    read_tree(tree);

    tree->root = 0;

    print_tree(tree);

    free_tree(tree);
    free(tree);
}
