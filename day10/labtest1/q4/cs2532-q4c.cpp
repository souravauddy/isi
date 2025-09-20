#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include "binary_trees.h"

int height(BINARY_TREE *tree, int node) {
    if (node == INT_NULL)
        return -1;

    return 1 + std::max<int>(height(tree, tree->nodes[node].left), height(tree, tree->nodes[node].right));
}

int depth(BINARY_TREE *tree, int node) {
    int depth = 0;

    while (tree->nodes[node].parent != INT_NULL) {
        depth++;
        node = tree->nodes[node].parent;
    }

    return depth;
}

int find_nearest_candidate(BINARY_TREE *tree) {
    std::queue<int> queue;
    queue.push(tree->root);

    auto candidate = [&](int node) -> bool {
        return tree->nodes[node].left != INT_NULL && tree->nodes[node].right != INT_NULL ? false : true;
    };

    while (!queue.empty()) {
        int node = queue.front();

        if (candidate(node))
            return node;

        if (tree->nodes[node].left != INT_NULL)
            queue.push(tree->nodes[node].left);

        if (tree->nodes[node].right != INT_NULL)
            queue.push(tree->nodes[node].right);
    }

    assert(false);
}

int main() {
    int capacity1, capacity2;
    BINARY_TREE *tree1 = (BINARY_TREE *) malloc(sizeof(BINARY_TREE *));
    BINARY_TREE *tree2 = (BINARY_TREE *) malloc(sizeof(BINARY_TREE *));
    BINARY_TREE *merged_tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE *));
    
    std::cin >> capacity1;
    init_tree(tree1, capacity1);
    read_tree(tree1);
    init_root(tree1, 0);

    std::cin >> capacity2;
    init_tree(tree2, capacity2);
    read_tree(tree2);
    init_root(tree2, 0);

    int node1 = find_nearest_candidate(tree1);
    int node2 = find_nearest_candidate(tree2);
    assert(node1 != INT_NULL && node2 != INT_NULL);

    int node1_depth = depth(tree1, node1);
    int node2_depth = depth(tree2, node2);
    int tree1_height = height(tree1, tree1->root);
    int tree2_height = height(tree2, tree2->root);

    init_tree(merged_tree, capacity1 + capacity2);
    int merge_index = 0;

    auto copy_tree = [&](BINARY_TREE *tree) -> void {
        std::queue<int> queue;
        queue.push(tree->root);
        int root_index = merge_index;

        while (!queue.empty()) {
            int node = queue.front();
            merged_tree->nodes[merge_index].data = tree->nodes[node].data;
            merged_tree->nodes[merge_index].left = root_index + tree->nodes[node].left;
            merged_tree->nodes[merge_index].right = root_index + tree->nodes[node].right;
            merged_tree->nodes[merge_index].parent = root_index + tree->nodes[node].parent;

            if (tree->nodes[node].left != INT_NULL)
                queue.push(tree->nodes[node].left);

            if (tree->nodes[node].right != INT_NULL)
                queue.push(tree->nodes[node].right);
        }
    };

    if (node1_depth + tree2_height > node2_depth + tree1_height) { // we swap
        BINARY_TREE *temp = tree1;
        tree1 = tree2;
        tree2 = temp;
    }
    
    copy_tree(tree1);
    copy_tree(tree2);

    print_tree(merged_tree);

    free_tree(tree1);
    free_tree(tree2);
    free_tree(merged_tree);
}
