#include <stdbool.h>
#include "avl_tree.h"
#include "../day11/binary_search_tree.h"

static inline int int_comparator(DATA data1, DATA data2) {
    return *((int *) data1) - *((int *) data2);
}

int min(const int a, const int b) {
    return a < b ? a : b;
}

int min3(const int a, const int b, const int c) {
    return min(a, min(b, c));
}

int max(const int a, const int b) {
    return a > b ? a : b;
}

int max3(const int a, const int b, const int c) {
    return max(a, max(b, c));
}

struct information {
    int min_value, max_value;
};

typedef struct information information;

bool leaf_node(const TREE *tree, const int node) {
    return tree->nodes[node].left == INT_NULL && tree->nodes[node].right == INT_NULL;
}

information check_valid_binary_search_tree(const TREE *tree, const int node, bool *valid) {
    information info;

    if (node == INT_NULL)
        return info;

    if (*valid == false)
        return info;

    if (leaf_node(tree, node)) {
        info.max_value = info.min_value = tree->nodes[node].data;
        return info;        
    }

    information left_info = check_valid_binary_search_tree(tree, tree->nodes[node].left, valid);
    information right_info = check_valid_binary_search_tree(tree, tree->nodes[node].right, valid);

    *valid |= tree->nodes[node].data > left_info.max_value && tree->nodes[node].data < right_info.min_value;
    info.min_value = min3(tree->nodes[node].data, left_info.min_value, right_info.min_value);
    info.max_value = max3(tree->nodes[node].data, left_info.max_value, right_info.max_value);

    return info;
}

bool check_binary_tree(const TREE *tree) {
    bool valid = false;

    check_valid_binary_search_tree(tree, tree->root, &valid);

    return valid;
}

int check_balanced(const TREE *tree, const int node, bool *valid) {
    if (node == INT_NULL)
        return 0;

    int left_subtree_height = check_balanced(tree, tree->nodes[node].left, valid);
    int right_subtree_height = check_balanced(tree, tree->nodes[node].right, valid);
    *valid |= left_subtree_height - right_subtree_height <= 1;

    return 1 + max(left_subtree_height, right_subtree_height);
}

bool check_height_balanced_tree(const TREE *tree) {
    bool balanced = true;

    check_balanced(tree, tree->root, &balanced);

    return balanced;
}

inline bool check_valid_avl_tree(const TREE *tree) {
    return check_binary_tree(tree) && check_height_balanced_tree(tree);
}

int main() {
    int capacity;
    scanf("%d", &capacity);
    TREE *tree = (TREE *) malloc(sizeof(TREE));

    init_tree(tree, capacity, sizeof(int), int_comparator);

    int root;
    scanf("%d", &root);
    init_root(tree, root);

    puts(check_valid_avl_tree(tree) ? "YES" : "NO");

    free_tree(tree);
}
