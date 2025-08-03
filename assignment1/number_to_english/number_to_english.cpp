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

constexpr const int MAX_UNITS = int(4);
constexpr const int MAX_NUMBER = int(6);
constexpr const int MAX_SIZE = int(1e2 + 7);

const std::array<int, MAX_UNITS> JUMPS = {1, 2, 1, 2};
const std::array<std::string, MAX_UNITS> UNITS = {"lakh", "thousand", "hundred", ""};

constexpr void initialize_digit(std::unordered_map<std::string, std::string> &digit_to_english) noexcept {
    digit_to_english["1"] = "one";
    digit_to_english["2"] = "two";
    digit_to_english["3"] = "three";
    digit_to_english["4"] = "four";
    digit_to_english["5"] = "five";
    digit_to_english["6"] = "six";
    digit_to_english["7"] = "seven";
    digit_to_english["8"] = "eight";
    digit_to_english["9"] = "nine";
    digit_to_english["10"] = "ten";
    digit_to_english["11"] = "eleven";
    digit_to_english["12"] = "twelve";
    digit_to_english["13"] = "thirteen";
    digit_to_english["14"] = "fourteen";
    digit_to_english["15"] = "fifteen";
    digit_to_english["16"] = "sixteen";
    digit_to_english["17"] = "seventeen";
    digit_to_english["18"] = "eighteen";
    digit_to_english["19"] = "nineteen";
    digit_to_english["20"] = "twenty";
    digit_to_english["30"] = "thirty";
    digit_to_english["40"] = "forty";
    digit_to_english["50"] = "fifty";
    digit_to_english["60"] = "sixty";
    digit_to_english["70"] = "seventy";
    digit_to_english["80"] = "eighty";
    digit_to_english["90"] = "ninety";
    digit_to_english["00"] = digit_to_english["0"] = "";
}

std::string formatted_number(const std::string &number) {
    std::string formatted_number_string(MAX_NUMBER, '0');
    int index = MAX_NUMBER - number.size();

    for (int i = 0; i < number.size(); i++)
        formatted_number_string[index++] = number[i];

    return formatted_number_string;
}

std::string create_translation(std::vector<std::string> &intermediates) noexcept {
    std::string translated;
    translated.reserve(MAX_SIZE);

    for (int i = 0; i < intermediates.size() - 1; i++)
        if (!intermediates[i].empty())
            translated.append(intermediates[i] + " ");
    translated.append(intermediates.back());

    return translated;
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    std::unordered_map<std::string, std::string> digit_to_english;
    initialize_digit(digit_to_english);

    std::string number(MAX_NUMBER, '0');
    std::getline(std::cin, number);
    
    std::vector<std::string> intermediates;
    number = formatted_number(number);

    auto format_place = [&](const std::string &place, int unit_location) -> void {
        if (!std::stoi(place))
            return;
        
        try {
            intermediates.push_back(digit_to_english.at(place));
        } catch (std::out_of_range exception) {
            intermediates.push_back(digit_to_english.at(std::string({place[0], '0'})));
            intermediates.push_back(digit_to_english.at(std::string({place[1]})));
        }

        intermediates.push_back(UNITS[unit_location]);
    };

    int index = 0, jump_index = 0;

    while (index < number.size()) {
        std::string place = number.substr(index, JUMPS[jump_index]);
        format_place(place, jump_index);
        index += JUMPS[jump_index];
        jump_index++;
    }

    std::cout << create_translation(intermediates) << '\n';
}

/*
9 99 9 99
9 lakh 99 thousand 9 hundred 99
9 lakh 99 thousand 9 hundred 9 ninety 9 nine
*/
