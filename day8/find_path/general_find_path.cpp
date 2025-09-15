#include "../binary_trees.h"
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
    for (int node1 = 0; node1 < tree->capacity; node1++) {
        for (int node2 = node1 + 1; node2 < tree->capacity; node2++) {
            if (path_sum(tree, node1, node2) == target) {
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
    init_root(tree, 0);

    int target;
    std::cin >> target;

    std::cout << find_path(tree, target) << '\n';

    free_tree(tree);
}
