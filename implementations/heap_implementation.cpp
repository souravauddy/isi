#include <iostream>
#include <exception>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <typeinfo>

[[nodiscard]]
inline size_t max(size_t a, size_t b) {
    return a > b ? a : b;
}

class empty_heap_exception : public std::exception {
public:

    const char * what() const noexcept override {
        return "heap is empty";
    }
};

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

template<typename Type, typename type_comparator = std::greater<Type>>
void build_heap(Type *array, size_t size) {
    Type *heap = (Type *) malloc((size + 1) * sizeof(Type));
    type_comparator comparator;

    auto valid_node = [&](int node) -> bool {
        return node <= size;
    };

    for (int i = 0; i < size; i++)
        heap[i + 1] = array[i];

    for (int node = size >> 1; node > 0; node--) {
        int current = node;

        while (valid_node(current)) {
            int next = current;

            if (valid_node(2 * current) && comparator(heap[current], heap[2 * current]))
                next = 2 * current;

            if (valid_node(2 * current + 1) && comparator(heap[current], heap[2 * current + 1]))
                next = 2 * current + 1;

            if (current == next)
                break;

            current = next;
        }
    }

    for (int i = 0; i < size; i++)
        array[i] = heap[i + 1];

    free(heap);
}

int main() {
    int array[] = {20, 30, 5, 222, 55, 2928};

    build_heap<int, std::less<int>>(array, 6);

    priority_queue<int, decltype(
        [](int a, int b) -> bool {
            return a < b;
        }
    )> heap(array, 6);
    // priority_queue<std::string, std::less<std::string>> heap;

    // heap.insert(std::string("sourav"));
    // heap.insert(std::string("auddy"));

    
    heap.insert(20);
    heap.insert(30);
    heap.insert(5);
    heap.insert(222);
    heap.insert(55);
    heap.insert(2);
    

    while (!heap.empty()) {
        auto x = heap.top();
        heap.pop();

        std::cout << x << '\n';
    }
}

// 1 2 3 4 5 6

/*
        
*/