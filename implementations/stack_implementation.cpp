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
        array_stack = (Type *) realloc(array_stack, this->capacity);
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

    void print() const noexcept {
        for (int i = tos - 1; i >= 0; i--)
            std::cout << array_stack[i] << '\n';
    }

    ~stack() {
        free(this->array_stack);
    }
};

int main() {
    int array[] = {1, 49, 288, 2848, 208, 224};
    stack<int, FIXED_SIZE_MODE> stck;

    for (int i = 0; i < 6; i++)
        stck.push(array[i]);

    stck.print();
    
    while (!stck.empty()) {
        auto x = stck.top();
        stck.pop();

        std::cout << x << '\n';
    }

}
