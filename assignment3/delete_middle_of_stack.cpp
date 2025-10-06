#include <iostream>
#include <exception>

class stack_overflow_exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "Stack Overflow";
    }
};

class stack_underflow_exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "Stack Underflow";
    }
};

enum MODE {
    FIXED_SIZE_MODE,
    VARIABLE_SIZE_MODE,
};

template<typename Type = int, size_t MODE = VARIABLE_SIZE_MODE>
class stack {
    inline constexpr static const int MIN_CAPACITY = int(20);

    Type *array_stack;
    int capacity, tos;

    void increase_capacity() {
        this->capacity = 2 * this->capacity;
        array_stack = (Type *) realloc(array_stack, this->capacity * sizeof(Type));
    }

public:

    stack(int capacity = stack::MIN_CAPACITY) {
        array_stack = (Type *) malloc(capacity * sizeof(Type));
        this->capacity = capacity;
        this->tos = 0;
    }

    void push(Type x) {
        if (tos == capacity) {
            if (MODE == FIXED_SIZE_MODE)
                throw stack_overflow_exception();

            increase_capacity();
        }
        
        array_stack[tos++] = x;
    }

    [[nodiscard]]
    Type top() const {
        if (tos <= 0)
            throw stack_underflow_exception();
        
        return array_stack[tos - 1];
    }

    void pop() {
        if (tos <= 0)
            throw stack_underflow_exception();

        --tos;
    }

    [[nodiscard]]
    bool empty() const {
        return tos <= 0;
    }

    [[nodiscard]]
    int size() const {
        return tos;
    }

    void print() const noexcept {
        for (int i = tos - 1; i >= 0; i--)
            std::cout << array_stack[i] << '\n';
    }

    ~stack() {
        free(this->array_stack);
    }
};

void delete_middle_of_stack(stack<int> &stck) {
    const int N = stck.size();
    stack<int> another_stack;

    for (int i = 0; i <= N / 2; i++) {
        another_stack.push(stck.top());
        stck.pop();
    }

    another_stack.pop();

    while (!another_stack.empty()) {
        stck.push(another_stack.top());
        another_stack.pop();
    }
}

int main() {
    stack<int> stck, another_stack;
    int array[] = {1, 49, 288, 2848, 208, 224, 5284, 24, 287, 281, 118, -4, -114};

    for (int i = 0; i < 13; i++)
        stck.push(array[i]);

    delete_middle_of_stack(stck);
    stck.print();
}
