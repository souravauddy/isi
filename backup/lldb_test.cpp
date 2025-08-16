#include <iostream>

int global = 20;

struct demo {
public:
    int member;

    void function() {
        std::cout << "I am in the class method" << '\n';
    }
};

int square(int value) {
    return value * value;
}

namespace LLDB_Demo {
    int add(int a, int b) {
        return a + b;
    }
}

int main(const int argc, const char **argv, const char **envp, const char **apple) {
    if (argc > 1)
        std::cout << argv[1] << '\n';

    int value = 5, result = square(value);

    std::cout << LLDB_Demo::add(20, 30) << '\n';
}