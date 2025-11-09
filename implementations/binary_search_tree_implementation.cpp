#include <iostream>
#include <numeric>
#include <ranges>
#include <random>
#include <vector>

const int INT_NULL = int(-1);

struct pair {
    int first, second;
};

template<typename Type>
struct node {
    inline constexpr static const Type SENTINEL = std::numeric_limits<Type>::max();

    Type data;
    int left, right;

    node() : data(node<Type>::SENTINEL), left(INT_NULL), right(INT_NULL) {}
};

template<typename Type>
class binary_search_tree {
    inline constexpr static const size_t MIN_CAPACITY = size_t(20);

    std::vector<node<Type>> nodes;
    size_t capacity, number_of_nodes;
    int free, root;

    void increase_capacity() {
        this->capacity = 2 * this->capacity;
        this->nodes.resize(this->capacity);

        for (int i = this->capacity >> 1; i < this->capacity; i++)
            this->nodes[i].right = i + 1;

        this->nodes[this->capacity - 1].right = INT_NULL;
        this->free = this->capacity >> 1;
    }

    [[nodiscard]]
    int insert_node(const int node, const Type &data) noexcept {
        if (node == INT_NULL) {
            if (free == INT_NULL)
                increase_capacity();

            int previous_free = free;
            nodes[free].data = data;
            free = nodes[free].right;
            nodes[previous_free].right = INT_NULL;
            number_of_nodes++;
            return previous_free;
        }

        if (nodes[node].data > data)
            nodes[node].left = insert_node(nodes[node].left, data);

        if (nodes[node].data < data)
            nodes[node].right = insert_node(nodes[node].right, data);
        
        return node;
    }

    void free_node(const int node) noexcept {
        nodes[node].left = INT_NULL;
        nodes[node].right = free;
        nodes[node].data = ::node<Type>::SENTINEL;
        free = node;
    }

    [[nodiscard]]
    int erase_node(const int node, const Type &data) noexcept {
        if (node == INT_NULL)
            return INT_NULL;
        
        if (nodes[node].data > data) {
            nodes[node].left = erase_node(nodes[node].left, data);
            return node;
        }

        if (nodes[node].data < data) {
            nodes[node].right = erase_node(nodes[node].right, data);
            return node;
        }

        int left_child = nodes[node].left, right_child = nodes[node].right;
        number_of_nodes--;

        if (left_child != INT_NULL && right_child != INT_NULL) {                
            if (nodes[right_child].left == INT_NULL) {
                nodes[right_child].left = nodes[node].left;
                free_node(node);
                return right_child;
            }

            int current = right_child;

            while (nodes[current].left != INT_NULL && nodes[nodes[current].left].left != INT_NULL)
                current = nodes[current].left;
            
            int sucessor = nodes[current].left;
            nodes[current].left = nodes[sucessor].right;
            nodes[sucessor].left = nodes[node].left;
            nodes[sucessor].right = right_child;
            free_node(node);
            return sucessor;
        }

        free_node(node);

        if (left_child != INT_NULL)
            return left_child;
        
        if (right_child != INT_NULL)
            return right_child;

        return INT_NULL;
    }

public:

    binary_search_tree(size_t capacity = binary_search_tree::MIN_CAPACITY) : root(INT_NULL), free(0), number_of_nodes(0) {
        this->capacity = std::max<size_t>(capacity, binary_search_tree::MIN_CAPACITY);
        nodes.resize(this->capacity);

        for (int i = 0; i < this->capacity; i++)
            nodes[i].right = i + 1;

        nodes[this->capacity - 1].right = INT_NULL;
    }

    [[nodiscard]]
    int get_root() const noexcept {
        return this->root;
    }

    void read(const int ROOT = int(0)) {
        std::cin >> capacity;
        nodes.resize(capacity);

        for (int i = 0; i < capacity; i++)
            std::cin >> nodes[i].data >> nodes[i].left >> nodes[i].right;

        this->root = ROOT;
    }

    void init_root(const int root = int(0)) noexcept {
        this->root = root;
    }

    [[nodiscard]]
    const node<Type>& operator[](const int index) const {
        return nodes[index];
    }

    [[nodiscard]]
    node<Type>& operator[](const int index) {
        return nodes[index];
    }

    void insert(const Type &data) {
        this->root = insert_node(this->root, data);
    }

    void erase(const Type &data) {
        this->root = erase_node(this->root, data);
    }

    void dump(FILE *file = stderr) {
        std::println(file, "{}", this->capacity);

        for (int i = 0; i < this->capacity; i++)
            std::println(file, "{} {} {}", nodes[i].data == ::node<Type>::SENTINEL ? int(1e9 + 5) : nodes[i].data, nodes[i].left, nodes[i].right);

        std::println(file, "{}", root);
    }
};

void inorder(binary_search_tree<int> &tree, const int node) {
    if (node == INT_NULL)
        return;

    inorder(tree, tree[node].left);
    std::println("{} ", tree[node].data);
    inorder(tree, tree[node].right);
}

int main() {
    binary_search_tree<int> tree;
    std::vector<int> values{20, 40, 15, 2, 205, 29};

    pair p;
    p.first = 20;
    p.second = 40;

    for (const int value : values)
        tree.insert(value);

    inorder(tree, tree.get_root());

    tree.erase(20);
    tree.erase(29);
    tree.erase(15);
    tree.erase(40);

    // for (const int value : values)
    //     tree.insert(value);

    // for (int i = 0; i < 30; i++)
    //     tree.insert(i);

    // inorder(tree, tree.get_root());

    // tree.erase(0);

    // tree.erase(14);
    // tree.erase(26);
    // tree.erase(13);

    tree.dump();
}
