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
#include <queue>
#include <stack>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>

using namespace std;

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
    cerr << endl;
}

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) 
        os << other[i] << ' ';
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

const int ALPHABET = int(26);
const char MIN_CHAR = char('A');
const char NULL_CHAR = char('\0');
const int INITIAL_STATE = int(0);

class DFA {
    vector<vector<int>> state_matrix;
    string pattern;
    int states = 0, iterator = 0, common_suffix_length = 0;
    char current_character;
    int FINAL_STATE;     

public:

    DFA(const string &_pattern) { 
        pattern = _pattern;
        states = pattern.length();
        state_matrix.assign(states + 1, vector<int>(ALPHABET, 0));
        FINAL_STATE = states;
    }

    void build() {
        state_matrix[0][pattern[0] - MIN_CHAR] = 1;

        for (int i = 1; i < states; i++) {
            for (int j = 0; j < ALPHABET; j++) {
                const char character = char(MIN_CHAR + j);
                state_matrix[i][j] = state_matrix[common_suffix_length][character - MIN_CHAR];
            }

            state_matrix[i][pattern[i] - MIN_CHAR] = i + 1;
            common_suffix_length = state_matrix[common_suffix_length][pattern[i] - MIN_CHAR];
        }

        for (int i = 0; i < ALPHABET; i++) 
            state_matrix[states][i] = state_matrix[common_suffix_length][i];
    }

    DFA& operator[](const char character) {
        current_character = character;
        return *this;
    }

    DFA& operator++(int) {
        iterator = state_matrix[iterator][current_character - MIN_CHAR];
        return *this;
    }

    bool reached_final_state() const {
        return iterator == FINAL_STATE;
    }
}; 

int main() {
    string sentence, pattern;   
    cin >> sentence >> pattern;
    const int N = int(sentence.size());
    int count_occurence = 0;
    int count_set_bits = 0;

    DFA dfa(pattern);
    dfa.build();  

    for (int i = 0; i < N; i++) {
        dfa[sentence[i]]++; 
        count_occurence += dfa.reached_final_state();
    }

    cout << "The number of times the pattern has appeared in the string is " << count_occurence << '\n';
}

/*
ABABA ABA
ACACAGACACAGA ACACAGA
*/