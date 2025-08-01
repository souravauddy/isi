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
#include <queue>
#include <stack>
#include <climits>
#include <unordered_set>
#include <unordered_map>
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


constexpr const double INCREMENT = (double) 1 / 37;


[[nodiscard]]
bool valid_guess(const char guess) noexcept {
    return guess == '_' || std::isdigit(guess) || std::isupper(guess) || std::islower(guess);
}

void simulate_round(int round, std::array<double, 2> &scores) {
    std::string transcript;
    std::getline(std::cin, transcript);

    std::cout << transcript << std::endl;

    std::stringstream in(transcript);
    std::string sequence, guess;
    in >> sequence, in >> guess;

    std::cout << sequence << std::endl << guess << std::endl;

    int current_player = round & 1, other_player = current_player ^ 1;
    std::unordered_set<char> present;

    for (const char character : sequence)
        present.insert(std::tolower(character));

    for (int i = 0; i < guess.size(); i++) {
        if (!valid_guess(guess[i])) {
            scores[current_player] += INCREMENT;
            return;
        }

        present.erase(std::tolower(guess[i]));

        if (present.empty()) {
            scores[other_player] += (double) 1 / (i + 1);
            return;
        }
    }

    scores[current_player] += INCREMENT;
}


int main() {
    // std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    // std::cin.tie(nullptr);
#endif

    std::string string_round;
    std::getline(std::cin, string_round);
    int rounds = std::stoi(string_round);

    std::array<double, 2> scores;
    scores.fill(0);
    
    for (int round = 0; round < rounds; round++) {
        simulate_round(round, scores);
    }

    std::cout << std::setprecision(6) <<  scores[0] << ' ' << scores[1] << '\n';
}
