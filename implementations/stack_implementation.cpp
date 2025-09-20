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

template<typename Type = int>
class stack {
    Type *array_stack;
    int capacity, tos;
public:

    stack() = default;

    stack(int capacity) {
        array_stack = (Type *) malloc(capacity * sizeof(Type));
        this->capacity = capacity;
        this->tos = 0;
    }

    void push(int x) {
        if (tos == capacity)
            throw stack_overflow_exception();
        
        array_stack[tos++] = x;
    }

    int top() {
        if (tos <= 0)
            throw stack_underflow_exception();
        
        return array_stack[tos - 1];
    }

    int pop() {
        if (tos <= 0)
            throw stack_underflow_exception();

        return array_stack[--tos];
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
    int N;
    std::cin >> N;

    stack<int> stck(N);

    stck.push(100);
    stck.push(500);

    try {
        std::cout << stck.pop() << '\n';
        std::cout << stck.pop() << '\n';
        std::cout << stck.pop() << '\n';
    } catch (stack_underflow_exception &exception) {
        std::cout << exception.what() << '\n';
    }
}
