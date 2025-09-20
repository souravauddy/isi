#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <sstream>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <memory>

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

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int N, M;
    std::cin >> N;
    std::queue<int> queue1;

    for (int i = 0; i < N; i++) {
        int x;
        std::cin >> x;
        queue1.push(x);
    }

    std::stack<int> stack;
    std::vector<std::string> output_buffer;

    for (int i = 0; i < N; i++) {
        int x;
        std::cin >> x;

        if (!stack.empty() && stack.top() == x) {
            stack.pop();
            output_buffer.push_back("pop");
            output_buffer.push_back("enqueue");
            continue;
        }

        while (!queue1.empty()) {
            int front = queue1.front();
            queue1.pop();
            output_buffer.push_back("dequeue");

            if (front == x) {
                output_buffer.push_back("enqueue");
                break;
            }

            stack.push(front);
            output_buffer.push_back("push");
        }
    }

    if (!stack.empty()) {
        std::cout << "Not possible" << '\n';
        return 0;
    }

    for (std::string &operation : output_buffer)
        std::cout << operation << '\n';
}
