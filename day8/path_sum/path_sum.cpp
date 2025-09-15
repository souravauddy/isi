#include "../binary_trees.h"
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

const int INF = int(1e9 + 5);

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

template<typename Type>
void output_vector(const std::vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    int capacity;
    std::cin >> capacity;
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));

    init_tree(tree, capacity);
    read_tree(tree);
    tree->root = 0;

    std::vector<int> leaves_index;

    y_combinator([&](auto self, int node) -> void {
        if (node == INT_NULL)
            return;

        if (tree->nodes[node].left == INT_NULL && tree->nodes[node].right == INT_NULL) {
            leaves_index.push_back(node);
            return;
        }

        self(tree->nodes[node].left);
        self(tree->nodes[node].right);
    })(tree->root);

    const int N = int(leaves_index.size());
    int max_path_sum = -INF;
    std::pair<int, int> max_leaf_pair;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int sum = path_sum(tree, leaves_index[i], leaves_index[j]);

            if (sum > max_path_sum) {
                max_path_sum = sum;
                max_leaf_pair = {leaves_index[i], leaves_index[j]};
            }
        }
    }

    std::cout << max_leaf_pair.first << ' ' << max_leaf_pair.second << ' ' << max_path_sum << '\n';
    
    free_tree(tree);
}
