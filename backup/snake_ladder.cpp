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
#include <random>
#include <vector>
#include <sstream>
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

constexpr const int BOARD_DIMENSION = int(14 - 4);
constexpr const char NEUTRAL = char('N');
constexpr const char SNAKE = char('S');
constexpr const char LADDER = char('L');
constexpr const char MIN_DIGIT = char('0');

struct state {
    int position, next;
    char type;

    state(int _position = int(-1), char _type = char(NEUTRAL), int _next = int(-1)) : position(_position), type(_type), next(_next) {}
};

int parse_string(const std::string &str) {
    int number = 0;
    std::string another;

    if (str.find("Start") != std::string::npos)
        return 0;

    if (str.find("End") != std::string::npos)
        return 100;

    for (int i = 2; i < int(str.length() - 1); i++)
        number = (number * 10) + (str[i] - MIN_DIGIT);

    return number;
}

void generate_board(std::vector<std::vector<int>> &board) {
    int start = 1;

    for (int d = BOARD_DIMENSION - 1; d >= 0; d--) {
        std::iota(board[d].begin(), board[d].end(), start);
        start += BOARD_DIMENSION;

        if (d % 2 == 0)
            std::reverse(board[d].begin(), board[d].end());
    }
}

int_fast32_t main(const int argc, const char **argv, const char **envp, const char **apple) {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif

    std::vector<std::vector<int>> default_board(BOARD_DIMENSION, std::vector<int>(BOARD_DIMENSION));
    generate_board(default_board);

    // for (int i = 0; i < BOARD_DIMENSION; i++) {
    //     for (int j = 0; j < BOARD_DIMENSION; j++)
    //         std::cout << default_board[i][j] << ' ';

    //     std::cout << '\n';
    // }

    // return 0;
    
    std::vector<std::string> string_board(BOARD_DIMENSION);

    for (std::string &row : string_board)
        std::getline(std::cin, row);
    
    std::string dice_rolls;
    std::getline(std::cin, dice_rolls);

    std::stringstream in(dice_rolls);
    std::vector<int> rolls;
    std::string roll;

    while (in >> roll)
        rolls.push_back(std::stoi(roll));

    // debug(rolls);

    std::vector<std::vector<state>> board(BOARD_DIMENSION);

    for (int d = 0; d < BOARD_DIMENSION; d++) {
        std::string &row = string_board[d];
        std::stringstream in(row);
        std::string token;

        for (int index = 0; in >> token; index++) {
            if (token.find("End") != std::string::npos) {
                board[d].emplace_back(100, NEUTRAL, -1);
                continue;
            }

            if (token.find("Start") != std::string::npos) {
                board[d].emplace_back(1, NEUTRAL, -1);
                continue;
            }
        
            const char type = token[0];

            if (std::isdigit(type)) {
                // debug(stoi(token), default_board[d][index], d, index);
                // assert(stoi(token) == default_board[d][index]);
                board[d].emplace_back(std::stoi(token), NEUTRAL, -1);
                continue;
            }
            
            assert(type == SNAKE || type == LADDER);
            board[d].emplace_back(default_board[d][index], type, parse_string(token));
        }
    }

    // return 0;

    // for (int i = 0; i < BOARD_DIMENSION; i++) {
    //     for (int j = 0; j < BOARD_DIMENSION; j++)
    //         std::cout << '(' << board[i][j].type << ' ' << board[i][j].position << ' ' << board[i][j].next << ") ";

    //     std::cout << '\n';
    // }

    std::map<int, std::array<int, 2>> co_ordinate_finder;

    for (int row = 0; row < BOARD_DIMENSION; row++)
        for (int column = 0; column < BOARD_DIMENSION; column++)
            co_ordinate_finder[default_board[row][column]] = {row, column};

    int ladder_count = 0, snake_count = 0, position = 0;

    for (const int roll : rolls) {
        if (position + roll > 100)
            continue;

        position += roll;

        const std::array<int, 2> &co_ordinate = co_ordinate_finder.at(position);
        int row = co_ordinate[0], column = co_ordinate[1];

        if (position == 100) {
            std::cout << "Possible " << snake_count << ' ' << ladder_count << '\n';
            return 0;
        }

        if (board[row][column].type != NEUTRAL) {
            snake_count += board[row][column].type == SNAKE;
            ladder_count += board[row][column].type == LADDER;
            position = board[row][column].next;
        }

        if (position == 100) {
            std::cout << "Possible " << snake_count << ' ' << ladder_count << '\n';
            return 0;
        }
    }

    std::cout << "Not possible " << snake_count << ' ' << ladder_count << ' ' << position << '\n';
}
