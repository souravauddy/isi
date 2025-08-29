#include "binary_trees.h"
#include <iostream>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int find_index(BINARY_TREE *tree, int node, int target) {
    if (node == INT_NULL)
        return -1;

    if (tree->nodes[node].data == target)
        return node;

    int index = find_index(tree, tree->nodes[node].left, target);
    
    if (index == INT_NULL)
        index = find_index(tree, tree->nodes[node].right, target);

    return index;
}

int path_length(BINARY_TREE *tree, int node) {
    int length = 0;

    while (node != tree->root) {
        length++;
        node = tree->nodes[node].parent;
    }

    return length;
}

int find_lca(BINARY_TREE *tree, int first_node, int second_node) {
    int first_node_index = find_index(tree, tree->root, first_node), second_node_index = find_index(tree, tree->root, second_node);
    int first_node_path_length = path_length(tree, first_node_index), second_node_path_length = path_length(tree, second_node_index);

    int difference = first_node_path_length - second_node_path_length;

    if (difference < 0)
        swap(first_node_index, second_node_index);

    difference = abs(difference);

    while (difference-- > 0)
        first_node_index = tree->nodes[first_node_index].parent;
 
    while (first_node_index != second_node_index) {
        first_node_index = tree->nodes[first_node_index].parent;
        second_node_index = tree->nodes[second_node_index].parent;
    }

    return first_node_index;
}

int main() {
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));
    assert(tree);

    int capacity;
    std::cin >> capacity;

    init_tree(tree, capacity);
    read_tree(tree);

    tree->root = 0;

    int first_node, second_node;
    std::cin >> first_node >> second_node;

    int lca = find_lca(tree, first_node, second_node);

    std::cout << tree->nodes[lca].data << '\n';

    free_tree(tree);
}
