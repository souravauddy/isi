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
#include <queue>
#include <stack>
#include <climits>
#include <sstream>
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

    int M, N, rows, columns;
    std::cin >> M >> N;
    rows = int(std::pow(10, M)), columns = int(std::pow(10, N));

    std::vector<std::vector<std::string>> matrix(rows);

    for (int r = 0; r < rows; r++) {
        std::string row, number;
        std::getline(std::cin, row);
        std::stringstream in(row);

        while (in >> number) {
            std::string fixed_number(M + N, '0');
            int index = M + N - 1;
            int number_index = number.size() - 1;

            while (number_index > 0)
                fixed_number[index--] = number[index--];

            matrix[r].push_back(number);
        }
    }

    auto treasure = [&](int row, int column) -> bool {
        int first_part = std::stoi(matrix[row][column].substr(0, M)), second_part = std::stoi(matrix[row][column].substr(M, N));
        return first_part == row && second_part == column;
    };

    auto next_location = [&](std::string &location) -> std::array<int, 2> {
        return {std::stoi(location.substr(0, M)), std::stoi(location.substr(M, N))};
    };

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (treasure(r, c))
                std::cout << '(' << r << ", " << c << ')' << '\n';
        }
    }

    std::set<std::array<int, 2>> visited;
    std::array<int, 2> position = {0, 0};

    do {
        visited.insert(position);
        std::cout << '(' << position[0] << ", " << position[1] << ')' << '\n';

        if (treasure(position[0], position[1])) {
            std::cout << "Treasure Found" << '\n';
            return 0;
        }

        position = next_location(matrix[position[0]][position[1]]);
    } while (!visited.count(position));

    std::cout << '(' << position[0] << ", " << position[1] << ')' << '\n';
    std::cout << "Going round in cirices" << '\n';
}
