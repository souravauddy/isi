#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <memory>

// using namespace std;

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
    
    std::string line;
    std::getline(std::cin, line);
    std::array<std::string, 2> numbers;
    std::array<int, 2> integer_numbers;
    std::stringstream in(line);

    for (int i = 0; in >> numbers[i]; i++);

    const int N = int(numbers[0].length()), M = int(numbers[1].length());

    if (N < M) {
        std::cout << "Impossible" << '\n';
        return 0;
    }

    for (int i = 0; i < 2; i++)
        integer_numbers[i] = std::stoi(numbers[i]);

    std::vector<char> sorted_characters(numbers[0].begin(), numbers[0].end());
    std::sort(sorted_characters.begin(), sorted_characters.end());
    std::string constructed_number, answer;
    std::vector<bool> used(N, false);
    bool possible = false;

    std::function<void(int)> recurse = [&](int index) -> void {
        if (index == M) {
            if (std::stoi(constructed_number) > integer_numbers[1]) {
                answer = constructed_number;
                possible = true;
            }

            return;
        }

        int lower_bound_index = int(std::lower_bound(sorted_characters.begin(), sorted_characters.end(), numbers[1][index]) - sorted_characters.begin());

        for (int i = lower_bound_index; i < N && !possible; i++) {
            if (used[i])
                continue;

            constructed_number.push_back(sorted_characters[lower_bound_index]);
            used[i] = true;
            recurse(index + 1);

            if (!possible) {
                used[i] = false;
                constructed_number.pop_back();
            }
        }
    };

    recurse(0);

    for (int i = 0; i < N; i++)
        if (!used[i])
            answer.push_back(sorted_characters[i]);

    std::cout << (possible ? answer : "Impossible") << '\n';
}

