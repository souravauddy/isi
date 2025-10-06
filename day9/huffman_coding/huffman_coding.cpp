#include <iostream>
#include <exception>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <typeinfo>

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

const int MAX_SIZE = int(1e2 + 5);
const int TABLE_SIZE = int(75);
const char MIN_CHAR = char('0');
const int INT_NULL = int(-1);
const char INTERNAL_NODE_CHAR = char(':');

class empty_heap_exception : public std::exception {
public:
    const char * what() const noexcept override {
        return "heap is empty";
    }
};

[[nodiscard]]
inline size_t max(size_t a, size_t b) {
    return a > b ? a : b;
}

[[nodiscard]]
inline bool valid_character(const char character) {
    return isdigit(character) || islower(character) || isupper(character);
}

struct node {   
    char character;
    int left, right, parent, character_frequency;
};

inline bool leaf_node(node &node) {
    return node.character != INTERNAL_NODE_CHAR;
}

template<typename Type, typename type_comparator = std::greater<Type>>
class priority_queue {
    inline static constexpr const size_t ROOT = int(1);
    inline static constexpr const size_t MIN_CAPACITY = int(20);

    Type *heap;
    size_t capacity, insert_index;
    type_comparator comparator;

    [[nodiscard]]
    static inline size_t parent(size_t node) {
        return node >> 1;
    }

    [[nodiscard]]
    static inline size_t left_child(size_t node) {
        return 2 * node;
    }

    [[nodiscard]]
    static inline size_t right_child(size_t node) {
        return 2 * node + 1;
    }

    inline void swap(size_t node, size_t parent) {
        Type &temp = heap[0];
        temp = heap[node];
        heap[node] = heap[parent];
        heap[parent] = temp;
    }

    [[nodiscard]]
    inline bool valid_node(size_t node) const {
        return node < this->insert_index;
    }

    void heapify_up(size_t node) {
        size_t parent_node = parent(node);

        while (parent_node > 0) {
            if (comparator(heap[node], heap[parent_node])) {
                swap(node, parent_node);
                node = parent_node;
                parent_node = parent(node);
                continue;
            }

            break;
        }
    }

    void heapify_down(size_t node) {
        while (valid_node(node)) {
            size_t next = node;

            if (valid_node(left_child(node)) && comparator(heap[left_child(node)], heap[next]))
                next = left_child(node);

            if (valid_node(right_child(node)) && comparator(heap[right_child(node)], heap[next]))
                next = right_child(node);

            if (next == node)
                break;

            swap(node, next);
            node = next;
        }
    }

    void increase_capacity() {
        this->capacity *= 2;
        this->heap = (Type *) realloc(this->heap, this->capacity * sizeof(Type));
    }

    void init_heap(size_t capacity) {
        this->capacity = max(capacity + 1, priority_queue::MIN_CAPACITY);
        this->heap = (Type *) malloc(this->capacity * sizeof(Type));
        this->insert_index = 1;
    }

public:
    
    priority_queue(int capacity = priority_queue::MIN_CAPACITY) : comparator() {
        init_heap(max(capacity, priority_queue::MIN_CAPACITY));
    }

    priority_queue(type_comparator &_comparator) : comparator(_comparator) {
        init_heap(MIN_CAPACITY);
    }

    priority_queue(int capacity, type_comparator &_comparator) : comparator(_comparator) {
        init_heap(max(capacity, priority_queue::MIN_CAPACITY));
    }

    priority_queue(Type *array, size_t size) : comparator() {
        init_heap(size);
        this->insert_index = size + 1;

        for (int index = 0; index < size; index++)
            heap[index + 1] = array[index];

        for (int node = size >> 1; node > 0; node--)
            heapify_down(node);
    }

    [[nodiscard]]
    bool empty() const {
        return this->insert_index == 1;
    }

    [[nodiscard]]
    Type& top() const {
        if (this->empty())
            throw empty_heap_exception();

        return this->heap[ROOT];
    }

    void insert(Type element) noexcept {
        if (insert_index == this->capacity)
            this->increase_capacity();

        heap[insert_index] = element;
        heapify_up(insert_index);
        insert_index++;
    }

    [[nodiscard]]
    size_t size() const noexcept {
        return insert_index - 1;
    }

    void pop() {
        if (this->empty())
            throw empty_heap_exception();

        swap(ROOT, insert_index - 1);
        insert_index--;
        heapify_down(ROOT);
    }

    ~priority_queue() {
        free(this->heap);
    }
};

class binary_tree {
    inline constexpr static const int MIN_CAPACITY = int(20);

    int capacity, number_of_nodes, root, free;
    node *nodes;

    void increase_capacity() {
        nodes = (node *) realloc(nodes, 2 * this->capacity * sizeof(node));
        assert(nodes);

        for (int i = capacity; i < 2 * capacity; i++) {
            nodes[i].character = INTERNAL_NODE_CHAR;
            nodes[i].character_frequency = 0;
            nodes[i].left = nodes[i].parent = INT_NULL;
            nodes[i].right = i + 1; 
        }

        free = capacity;
        capacity = 2 * capacity;
        nodes[capacity - 1].right = INT_NULL;
    }

public:

    binary_tree(int capacity = binary_tree::MIN_CAPACITY) {
        this->capacity = capacity;
        this->root = 0;
        nodes = (node *) malloc(this->capacity * sizeof(node));
        assert(nodes);

        for (int i = 0; i < capacity; i++) {
            nodes[i].character = INTERNAL_NODE_CHAR;
            nodes[i].character_frequency = 0;
            nodes[i].left = nodes[i].parent = INT_NULL;
            nodes[i].right = i + 1;
        }

        nodes[capacity - 1].right = INT_NULL;
        free = 0;
    }
    
    void init_root(int root_index) {
        this->root = root_index;
    }

    int add_leaf_node(char character, int frequency) {
        if (number_of_nodes == capacity)
            increase_capacity();
        
        int previous_free = free;
        nodes[free].character = character;
        nodes[free].character_frequency = frequency;
        free = nodes[free].right;
        nodes[previous_free].right = INT_NULL;
        nodes[previous_free].left = INT_NULL;
        number_of_nodes++;

        return previous_free;
    }

    int add_internal_node(int index1, int index2) {
        if (number_of_nodes == capacity)
            increase_capacity();

        int next_free = nodes[free].right;
        nodes[free].left = index1;
        nodes[free].right = index2;
        nodes[index1].parent = free;
        nodes[index2].parent = free;
        nodes[free].character_frequency = nodes[index1].character_frequency + nodes[index2].character_frequency;
        free = next_free;
        number_of_nodes++;

        return nodes[index1].parent;
    }

    void print_tree() {
        for (int i = 0; i < capacity; i++)
            std::cout << nodes[i].character << ' ' << nodes[i].left << ' ' << nodes[i].right << ' ' << nodes[i].character_frequency << ' ' << nodes[i].parent << '\n';
    }

    [[nodiscard]]
    node& operator[](int index) const {
        return nodes[index];
    }

    [[nodiscard]]
    char * decode_message(const char *encoded_message) const {
        int encoded_message_length = strlen(encoded_message), index = 0;
        int node = root, decoded_string_index = 0;
        char *decoded_message = (char *) malloc(MAX_SIZE * sizeof(char));

        while (index < encoded_message_length) {
            if (leaf_node(nodes[node])) {
                decoded_message[decoded_string_index++] = nodes[node].character;
                node = root;
                continue;
            } else if (encoded_message[index] == '0') {
                node = nodes[node].left;
            } else if (encoded_message[index] == '1') {
                node = nodes[node].right;
            } else {
                decoded_message[decoded_string_index++] = encoded_message[index];
            }
            
            index++;
        }
        
        if (leaf_node(nodes[node]))
            decoded_message[decoded_string_index++] = nodes[node].character;

        decoded_message[decoded_string_index] = '\0';

        return decoded_message;
    }

    ~binary_tree() {
        ::free(this->nodes);
    }
};

int main() {    
    char input[MAX_SIZE];
    fgets(input, MAX_SIZE, stdin);
    int *frequency = (int *) malloc(TABLE_SIZE * sizeof(int));
    assert(frequency);

    for (int i = 0; i < TABLE_SIZE; i++)
        frequency[i] = 0;

    for (int i = 0; input[i] != '\n'; i++)
        if (valid_character(input[i]))
            frequency[input[i] - MIN_CHAR]++;

    binary_tree tree;

    auto comparator = [&](int index1, int index2) -> bool {
        return tree[index1].character_frequency < tree[index2].character_frequency;
    };

    priority_queue<int, decltype(comparator)> heap(comparator);

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (frequency[i] > 0) {
            int node_index = tree.add_leaf_node(char(i + MIN_CHAR), frequency[i]);
            heap.insert(node_index);
        }
    }

    while (heap.size() > 1) {
        int index1 = heap.top();
        heap.pop();
        int index2 = heap.top();
        heap.pop();

        int node_index = tree.add_internal_node(index1, index2);
        heap.insert(node_index);
    }

    char encoded_string[MAX_SIZE] = "0";
    int root_index = heap.top(), index = 0;
    tree.init_root(root_index);
    heap.pop();

    if (leaf_node(tree[root_index])) {
        std::cout << tree[root_index].character << ": " << 0 << '\n';
        return 0;
    }

    y_combinator([&](auto dfs, int node, int index) -> void {
        if (leaf_node(tree[node])) {
            std::cout << tree[node].character << ": ";
            encoded_string[index] = '\0';
            puts(encoded_string);
            return;
        }
        
        encoded_string[index] = '0';
        dfs(tree[node].left, index + 1);
        encoded_string[index] = '1';
        dfs(tree[node].right, index + 1);
    })(root_index, 0);

    char *decoded_message = tree.decode_message(
        "1010101100101110111011101100001101101101010101010111011"
    );
    puts(decoded_message);

    free(decoded_message);
    free(frequency);
}
