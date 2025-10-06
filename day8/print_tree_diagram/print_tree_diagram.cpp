#include "../binary_trees.h"
#include <iostream>
#include <vector>
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

#ifdef LOCAL
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

std::map<int, int> count_left_nodes(BINARY_TREE *tree) {
    std::map<int, int> number_of_left_nodes;
    int count = -1;

    y_combinator([&](auto self, int node) -> void {
        if (node == INT_NULL)
            return;

        self(tree->nodes[node].left);
        count = count + 1;
        number_of_left_nodes[node] = count;
        self(tree->nodes[node].right);
    })(tree->root);

    return number_of_left_nodes;
}

void print_tree_diagram(BINARY_TREE *tree) {
    std::map<int, int> number_of_left_nodes = count_left_nodes(tree);
    std::map<int, int> node_level;
    std::queue<int> queue1, queue2;
    int maximum_level = INT_MIN;
    char value = 'a';

    auto has_children = [&](int node) -> bool {
        return !(tree->nodes[node].left == INT_NULL && tree->nodes[node].right == INT_NULL);
    };

    y_combinator([&](auto self, int node, int level) -> void {
        if (node == INT_NULL)
            return;

        node_level[node] = level;
        maximum_level = std::max(maximum_level, level);
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
    
    int previous_level = 0;

    while (!queue2.empty()) {
        std::vector<int> sibling_nodes;

        while (!queue2.empty() && node_level.at(queue2.front()) == previous_level) {
            sibling_nodes.push_back(queue2.front());
            queue2.pop();
        }

        if (!sibling_nodes.empty()) {
            // printing the '-'s.
            {
                int parent = tree->nodes[sibling_nodes.front()].parent;

                if (parent != INT_NULL) {
                    if (tree->nodes[parent].left == sibling_nodes.front()) {
                        for (int space = 0; space < number_of_left_nodes.at(sibling_nodes.front()); space++)
                            std::cout << ' ';

                        for (int space = 0; space < number_of_left_nodes.at(parent) - number_of_left_nodes.at(sibling_nodes.front()) + 1; space++)
                            std::cout << '-';
                    } else {
                        for (int space = 0; space < number_of_left_nodes.at(parent); space++)
                            std::cout << ' ';

                        for (int space = 0; space < number_of_left_nodes.at(sibling_nodes.front()) - number_of_left_nodes.at(parent) + 1; space++)
                            std::cout << '-';
                    }

                    for (int node = 1; node < sibling_nodes.size(); node++) {
                        int parent1 = tree->nodes[sibling_nodes[node]].parent, parent2 = tree->nodes[sibling_nodes[node - 1]].parent;

                        if (parent1 == parent2) {
                            // debug(p(sibling_nodes[node]), p(sibling_nodes[node - 1]), p(parent1), p(tree->nodes[parent1].right), p(sibling_nodes[node]));
                            assert(tree->nodes[parent1].right == sibling_nodes[node]);
                            // this node is necessarily a right child.

                            for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(parent1); space++)
                                std::cout << '-';
                        } else {
                            if (tree->nodes[parent1].left == sibling_nodes[node]) {
                                // if the node is a left child

                                if (tree->nodes[parent2].right == sibling_nodes[node - 1]) {
                                    for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(sibling_nodes[node - 1]) - 1; space++)
                                        std::cout << ' ';

                                    for (int space = 0; space < number_of_left_nodes.at(parent1) - number_of_left_nodes.at(sibling_nodes[node]) + 1; space++)
                                        std::cout << '-';
                                } else {
                                    for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(parent2) - 1; space++)
                                        std::cout << ' ';

                                    for (int space = 0; space < number_of_left_nodes.at(parent1) - number_of_left_nodes.at(sibling_nodes[node]) + 1; space++)
                                        std::cout << '-';
                                }
                            } else {
                                if (tree->nodes[parent2].left == sibling_nodes[node - 1]) {
                                    for (int space = 0; space < number_of_left_nodes.at(parent1) - number_of_left_nodes.at(parent2) - 1; space++)
                                        std::cout << ' ';

                                    for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(parent1) + 1; space++)
                                        std::cout << '-';
                                } else {
                                    for (int space = 0; space < number_of_left_nodes.at(parent1) - number_of_left_nodes.at(sibling_nodes[node - 1]) - 1; space++)
                                        std::cout << ' ';

                                    for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(parent1) + 1; space++)
                                        std::cout << '-';
                                }
                            }
                        }
                    }
                }

                std::cout << '\n';
            }

            {
                if (previous_level > 0) {
                    for (int space = 0; space < number_of_left_nodes.at(sibling_nodes.front()); space++)
                        std::cout << ' ';

                    std::cout << '|';

                    for (int node = 1; node < sibling_nodes.size(); node++) {
                        for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(sibling_nodes[node - 1]) - 1; space++)
                            std::cout << ' ';
                        std::cout << '|';
                    }

                    std::cout << '\n';
                }
            }

            {
                for (int space = 0; space < number_of_left_nodes.at(sibling_nodes.front()); space++) {
                    std::cout << ' ';
                }

                std::cout << value;
                value = value >= 'z' ? 'a' : value + 1;

                for (int node = 1; node < sibling_nodes.size(); node++) {
                    for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(sibling_nodes[node - 1]) - 1; space++)
                        std::cout << ' ';

                    std::cout << value;
                    value = value >= 'z' ? 'a' : value + 1;
                }

                std::cout << '\n';
            }
            
            {
                for (int space = 0; space < number_of_left_nodes.at(sibling_nodes.front()); space++)
                    std::cout << ' ';

                std::cout << (has_children(sibling_nodes.front()) ? '|' : ' ');

                for (int node = 1; node < sibling_nodes.size(); node++) {
                    for (int space = 0; space < number_of_left_nodes.at(sibling_nodes[node]) - number_of_left_nodes.at(sibling_nodes[node - 1]) - 1; space++)
                        std::cout << ' ';

                    std::cout << (has_children(sibling_nodes[node]) ? '|' : ' ');
                }

                std::cout << '\n';
            }
        }

        previous_level++;
        sibling_nodes.clear();
    }
}

int main() {
    int capacity;
    std::cin >> capacity;
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));

    init_tree(tree, capacity);
    read_tree(tree);

    init_root(tree, 0);

    print_tree_diagram(tree);

    free(tree->nodes);
    free(tree);
}
