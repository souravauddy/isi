#include <iostream>
#include <numeric>
#include <vector>

const int INT_NULL = int(-1);

template<typename Type>
struct node {
    inline constexpr static const Type SENTINEL = std::numeric_limits<Type>::max();

    Type data;
    int left, right, parent;

    node() : data(node<Type>::SENTINEL), left(INT_NULL), right(INT_NULL), parent(INT_NULL) {}
};

template<typename Type>
class binary_tree {
    inline constexpr static const size_t MIN_CAPACITY = size_t(20);

    std::vector<node<Type>> nodes;
    size_t capacity, number_of_nodes;
    int root, free;

public:

    binary_tree(size_t capacity = binary_tree::MIN_CAPACITY) : number_of_nodes(0), root(INT_NULL), free(0) {
        this->capacity = std::max<size_t>(binary_tree::MIN_CAPACITY, capacity);
        nodes.resize(this->capacity);

        for (int i = 0; i < this->capacity; i++)
            nodes[i].right = i + 1;
        
        nodes[this->capacity - 1].right = INT_NULL;
    }

    void read(const int ROOT = int(0)) noexcept {
        std::cin >> this->capacity;
        nodes.resize(this->capacity);

        for (int i = 0; i < capacity; i++) {
            std::cin >> nodes[i].data >> nodes[i].left >> nodes[i].right;

            if (nodes[i].left != INT_NULL)
                nodes[nodes[i].left].parent = i;

            if (nodes[i].right != INT_NULL)
                nodes[nodes[i].right].parent = i;
        }

        root = ROOT;
        free = INT_NULL;
        number_of_nodes = capacity;
    }

    void init_root(const int root) noexcept {
        this->root = root;
    }

    void dump(FILE *file = stderr) const {
        std::println(file, "{}", capacity);

        for (int i = 0; i < capacity; i++)
            std::println(file, "{} {} {}", nodes[i].data, nodes[i].left, nodes[i].right);

        std::println(file, "{}", root);
    }

    [[nodiscard]]
    int get_root() const {
        return root;
    }

    void inorder(const int node) const {
        if (node == INT_NULL)
            return;

        inorder(nodes[node].left);
        std::println("{} ", nodes[node].data);
        inorder(nodes[node].right);
    }
};

int main() {
    binary_tree<int> tree;
    tree.read(0);

    tree.inorder(tree.get_root());

    tree.dump();
}
