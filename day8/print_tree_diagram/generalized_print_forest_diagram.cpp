#include "../binary_trees.h"
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <queue>
#include <map>

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) const {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

void debug_out() {
    std::cerr << std::endl;
}

template<typename Type>
std::ostream& operator<<(std::ostream &os, const std::vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) 
        os << other[i] << ", ";
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    std::cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

[[nodiscard]]
int width(const int value) {
    return std::to_string(value).length();
}

[[nodiscard]]
int width(const std::string &string) {
    return string.length();
}

[[nodiscard]]
int width(const double value) {
    int integer_part = int(value);
    int float_part = int(value - integer_part) * (1e6);
    return (std::to_string(integer_part) + "." + std::to_string(float_part)).length();
}

std::map<int, int> count_spaces_to_left(BINARY_TREE *tree) {
    std::map<int, int> spaces_to_the_left;
    int count = 0;

    y_combinator([&](auto self, int node) -> void {
        if (node == INT_NULL)
            return;

        self(tree->nodes[node].left);
        spaces_to_the_left[node] = count;
        count += width(tree->nodes[node].data);
        self(tree->nodes[node].right);
    })(tree->root);

    return spaces_to_the_left;
}

void print_tree_diagram(BINARY_TREE *tree) {
    std::map<int, int> spaces_to_left = count_spaces_to_left(tree);
    std::map<int, int> node_level;
    std::queue<int> queue1, queue2;
    int previous_level = 0;

    auto has_children = [&](int node) -> bool {
        return !(tree->nodes[node].left == INT_NULL && tree->nodes[node].right == INT_NULL);
    };

    y_combinator([&](auto self, int node, int level) -> void {
        if (node == INT_NULL)
            return;

        node_level[node] = level;
        self(tree->nodes[node].left, level + 1);
        self(tree->nodes[node].right, level + 1);
    })(tree->root, 0);

    queue1.push(tree->root);
    queue2.push(tree->root);

    while (!queue1.empty()) {
        int node = queue1.front();
        queue1.pop();

        if (tree->nodes[node].left != INT_NULL) {
            queue1.push(tree->nodes[node].left);
            queue2.push(tree->nodes[node].left);
        }

        if (tree->nodes[node].right != INT_NULL) {
            queue1.push(tree->nodes[node].right);
            queue2.push(tree->nodes[node].right);
        }
    }

    while (!queue2.empty()) {
        std::vector<int> sibling_nodes;

        while (!queue2.empty() && node_level.at(queue2.front()) == previous_level) {
            sibling_nodes.push_back(queue2.front());
            queue2.pop();
        }

        if (!sibling_nodes.empty()) {
            {
                int parent = tree->nodes[sibling_nodes.front()].parent;

                if (parent != INT_NULL) {
                    if (tree->nodes[parent].left == sibling_nodes.front()) {
                        for (int space = 0; space < spaces_to_left.at(sibling_nodes.front()) + width(tree->nodes[sibling_nodes.front()].data) / 2; space++)
                            std::cout << ' ';
                        
                        for (int space = 0; 
                            space < 1 + spaces_to_left.at(parent) - spaces_to_left.at(sibling_nodes.front()) + width(tree->nodes[parent].data) / 2 - width(tree->nodes[sibling_nodes.front()].data) / 2; 
                        space++) {
                            std::cout << '-';
                        }
                    } else {
                        for (int space = 0; space < spaces_to_left.at(parent) + width(tree->nodes[parent].data) / 2; space++)
                            std::cout << ' ';

                        for (int space = 0;
                            space < 1 + spaces_to_left.at(sibling_nodes.front()) - spaces_to_left.at(parent) - width(tree->nodes[parent].data) / 2 + width(tree->nodes[sibling_nodes.front()].data) / 2;
                        space++) {
                            std::cout << '-';
                        }
                    }

                    for (int node = 1; node < sibling_nodes.size(); node++) {
                        int parent1 = tree->nodes[sibling_nodes[node]].parent, parent2 = tree->nodes[sibling_nodes[node - 1]].parent;

                        if (parent1 == parent2) {
                            assert(tree->nodes[parent1].right == sibling_nodes[node]);

                            for (int space = 0; 
                                space < spaces_to_left.at(sibling_nodes[node]) - spaces_to_left.at(parent1) - width(tree->nodes[parent1].data) / 2 + width(tree->nodes[sibling_nodes[node]].data) / 2; 
                            space++) {
                                std::cout << '-';
                            }
                        } else {
                            if (tree->nodes[parent1].left == sibling_nodes[node]) {
                                if (tree->nodes[parent2].right == sibling_nodes[node - 1]) {
                                    for (int space = 0; 
                                        space < spaces_to_left.at(sibling_nodes[node]) - spaces_to_left.at(sibling_nodes[node - 1]) - width(tree->nodes[sibling_nodes[node - 1]].data) / 2 + width(tree->nodes[sibling_nodes[node]].data) / 2 - 1; 
                                    space++) {
                                        std::cout << ' ';
                                    }
                                    
                                    for (int space = 0; 
                                        space < 1 + spaces_to_left.at(parent1) - spaces_to_left.at(sibling_nodes[node]) + width(tree->nodes[parent1].data) / 2 - width(tree->nodes[sibling_nodes[node]].data) / 2; 
                                    space++) {
                                        std::cout << '-';
                                    } 
                                } else {
                                    for (int space = 0; 
                                        space < spaces_to_left.at(sibling_nodes[node]) - spaces_to_left.at(parent2) - width(tree->nodes[parent2].data) / 2 + width(tree->nodes[sibling_nodes[node]].data) / 2 - 1; 
                                    space++) {
                                        std::cout << ' ';
                                    }
                                    
                                    // std::cout << '-';
                                    for (int space = 0; 
                                        space < 1 + spaces_to_left.at(parent1) - spaces_to_left.at(sibling_nodes[node]) + width(tree->nodes[parent1].data) / 2 - width(tree->nodes[sibling_nodes[node]].data) / 2; 
                                    space++) {
                                        std::cout << '-';
                                    }
                                }
                            } else {
                                if (tree->nodes[parent2].left == sibling_nodes[node - 1]) {
                                    for (int space = 0; 
                                        space < spaces_to_left.at(parent1) - spaces_to_left.at(parent2) - width(tree->nodes[parent2].data) / 2 + width(tree->nodes[parent1].data) / 2 - 1;
                                    space++) {
                                        std::cout << ' ';
                                    }

                                    for (int space = 0;
                                        space < 1 + spaces_to_left.at(sibling_nodes[node]) - spaces_to_left.at(parent1) - width(tree->nodes[parent1].data) / 2 + width(tree->nodes[sibling_nodes[node]].data) / 2;
                                    space++) {
                                        std::cout << '-';
                                    }
                                } else {
                                    for (int space = 0; 
                                        space < spaces_to_left.at(parent1) - spaces_to_left.at(sibling_nodes[node - 1]) - width(tree->nodes[sibling_nodes[node - 1]].data) / 2 + width(tree->nodes[parent1].data) / 2 - 1;
                                    space++) {
                                        std::cout << ' ';
                                    }

                                    for (int space = 0;
                                        space < 1 + spaces_to_left.at(sibling_nodes[node]) - spaces_to_left.at(parent1) - width(tree->nodes[parent1].data) / 2 + width(tree->nodes[sibling_nodes[node]].data) / 2;
                                    space++) {
                                        std::cout << '-';
                                    }
                                }
                            }
                        }
                    }

                    std::cout << '\n';
                }
            }

            auto compute_spaces = [&](int node) -> int {
                assert(node - 1 >= 0);
                int spaces = spaces_to_left.at(sibling_nodes[node]) - spaces_to_left.at(sibling_nodes[node - 1]);
                int node1_width = width(tree->nodes[sibling_nodes[node - 1]].data);
                int node2_width = width(tree->nodes[sibling_nodes[node]].data);
                spaces -= node1_width / 2 + 1;
                spaces += node2_width / 2;
                return spaces;
            };

            {
                if (previous_level > 0) {
                    for (int space = 0; space < spaces_to_left.at(sibling_nodes.front()) + width(tree->nodes[sibling_nodes.front()].data) / 2; space++)
                        std::cout << ' ';

                    std::cout << '|';

                    for (int node = 1; node < sibling_nodes.size(); node++) {
                        for (int space = 0; space < compute_spaces(node); space++) {
                            std::cout << ' ';
                        }

                        std::cout << '|';
                    }

                    std::cout << '\n';
                }
            }

            {
                for (int space = 0; space < spaces_to_left.at(sibling_nodes.front()); space++)
                    std::cout << ' ';

                std::cout << tree->nodes[sibling_nodes.front()].data;

                for (int node = 1; node < sibling_nodes.size(); node++) {
                    for (int space = 0; space < spaces_to_left.at(sibling_nodes[node]) - (spaces_to_left.at(sibling_nodes[node - 1]) + width(tree->nodes[sibling_nodes[node - 1]].data)); space++) {
                        std::cout << ' ';
                    }

                    std::cout << tree->nodes[sibling_nodes[node]].data;
                }

                std::cout << '\n';
            }

            {
                for (int space = 0; space < spaces_to_left.at(sibling_nodes.front()) + width(tree->nodes[sibling_nodes.front()].data) / 2; space++)
                    std::cout << ' ';

                std::cout << (has_children(sibling_nodes.front()) ? '|' : ' ');

                for (int node = 1; node < sibling_nodes.size(); node++) {
                    for (int space = 0; space < compute_spaces(node); space++) {
                        std::cout << ' ';
                    }

                    std::cout << (has_children(sibling_nodes[node]) ? '|' : ' ');
                }

                std::cout << '\n';
            }
        }

        sibling_nodes.clear();
        previous_level++;
    }
}

int main() {
    int capacity;
    std::cin >> capacity;
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));
    int count_trees = 0;

    init_tree(tree, capacity);
    read_tree(tree);

    for (int node = 0; node < capacity; node++) {
        if (tree->nodes[node].data != SENTINEL && tree->nodes[node].parent == INT_NULL) {
            init_root(tree, node);
            std::println("Tree: {}", ++count_trees);
            std::println();
            print_tree_diagram(tree);
        }
    }

    free(tree->nodes);
    free(tree);
}
