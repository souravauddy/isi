#include <iostream>
#include <exception>
#include <cassert>

class empty_queue_exception : public std::exception {
public:

    const char * what() const noexcept override {
        return "Queue is empty";
    }
};

class full_queue_exception : public std::exception {
public:

    const char * what() const noexcept override {
        return "Queue is full";
    }
};

enum MODE {
    FIXED_SIZE_MODE,
    VARIABLE_SIZE_MODE,
};

template<typename Type, size_t MODE = VARIABLE_SIZE_MODE>
class queue {
    inline constexpr static const int MIN_SIZE = int(2);

    Type *array_queue;
    int front_pointer, rear_pointer, capacity, number_of_elements;

    [[nodiscard]]
    inline int mod(int x) const {
        return x >= capacity ? x - capacity : x;
    }

    void increase_capacity() {
        this->capacity *= 2;
        array_queue = (Type *) realloc(array_queue, this->capacity * sizeof(Type));
    }

public:

    queue(int capacity = queue::MIN_SIZE) {
        this->capacity = capacity;
        array_queue = (Type *) malloc(this->capacity * sizeof(Type));
        this->front_pointer = this->rear_pointer = -1;
        this->number_of_elements = 0;
        assert(array_queue);
    }

    void insert(Type value) {
        if (number_of_elements == capacity) {
            if (MODE == FIXED_SIZE_MODE)
                throw full_queue_exception();

            increase_capacity();
        }

        front_pointer = queue::mod(front_pointer + 1);
        array_queue[front_pointer] = value;
        number_of_elements++;
    }

    [[nodiscard]]
    Type front() const {
        if (number_of_elements == 0)
            throw empty_queue_exception();

        return array_queue[queue::mod(rear_pointer + 1)];
    }

    void pop() {
        if (number_of_elements == 0)
            throw empty_queue_exception();
            
        rear_pointer = queue::mod(rear_pointer + 1);
        number_of_elements--;
    }

    [[nodiscard]]
    bool empty() const noexcept {
        return number_of_elements == 0;
    }

    ~queue() {
        free(array_queue);
    }
};

int main() {
    int array[] = {1, 4, 29, 28, 22, 49};
    queue<int> que;

    for (int i = 0; i < 6; i++)
        que.insert(array[i]);

    while (!que.empty()) {
        auto front = que.front();
        que.pop();
        
        std::cout << front << '\n';
    }
}
