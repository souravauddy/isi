#include "binary_trees.h"
#include <iostream>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int path_length(BINARY_TREE *tree, int node) {
    int length = 0;

    while (node != tree->root) {
        length++;
        node = tree->nodes[node].parent;
    }

    return length;
}

int path_sum(BINARY_TREE *tree, int first_node_index, int second_node_index) {
    int first_node_path_length = path_length(tree, first_node_index), second_node_path_length = path_length(tree, second_node_index);
    int difference = first_node_path_length - second_node_path_length, sum = 0;

    if (difference < 0)
        swap(first_node_index, second_node_index);

    difference = abs(difference);

    while (difference-- > 0) {
        sum += tree->nodes[first_node_index].data;
        first_node_index = tree->nodes[first_node_index].parent;
    }
 
    while (first_node_index != second_node_index) {
        sum += tree->nodes[first_node_index].data + tree->nodes[second_node_index].data;
        first_node_index = tree->nodes[first_node_index].parent;
        second_node_index = tree->nodes[second_node_index].parent;
    }

    sum += tree->nodes[first_node_index].data;

    return sum;
}

bool find_path(BINARY_TREE *tree, int target) {
    for (int i = 0; i < tree->capacity; i++) {
        for (int j = i + 1; j < tree->capacity; j++) {
            if (path_sum(tree, i, j) == target) {
                std::cout << i << ' ' << j << '\n';
                return true;
            }
        }
    }

    return false;
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

    std::cout << find_path(tree, target) << '\n';

    free_tree(tree);
}
