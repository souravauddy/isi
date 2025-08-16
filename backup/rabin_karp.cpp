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

const int ALPHABET = int(256);
const int PRIME = int(13);
const int BASE = int(PRIME - 3);
const char MIN_CHAR = char('A');

int main() {
    string sentence, pattern;
    cin >> sentence >> pattern;
    const int N = int(sentence.length());
    const int M = int(pattern.length());
    map<char, int> character_value;

    auto binpow = [&](int number, int power) {
        int result = 1;
        
        while (power > 0) {
            if (power & 1)
                result = (result * number) % PRIME;

            number = (number * number) % PRIME;
            power >>= 1;
        }

        return result;
    };

    const int HASHING_FACTOR = int(binpow(BASE, M - 1));

    debug(HASHING_FACTOR);

    for (int i = 0; i < ALPHABET; i++)
        character_value[char(MIN_CHAR + i)] = i + 1;

    auto hash = [&](const string &S) -> int {
        int power = HASHING_FACTOR;
        int hash_value = 0;

        for (int i = 0; i < M; i++) {
            hash_value = (hash_value + (character_value[S[i]] * power)) % PRIME;
            // hash_value = (ALPHABET * hash_value + character_value[S[i]]) % PRIME;    // this works for ALPHABET
            power /= BASE;
        }

        return hash_value;
    };

    auto rehash = [&](int index, int previous_hash) -> int {
        return ((BASE * (previous_hash - character_value[sentence[index]] * HASHING_FACTOR)) + character_value[sentence[index + M]]) % PRIME;
    };

    int pattern_hash = hash(pattern);
    int current_hash = hash(sentence.substr(0, M));
    int count_occurence = 0;

    debug(pattern_hash);

    for (int i = 0; i <= N - M; i++) {
        if (current_hash == pattern_hash) 
            count_occurence += sentence.substr(i, M) == pattern;

        current_hash = rehash(i, current_hash);
        current_hash = current_hash < 0 ? (PRIME + current_hash) % PRIME : current_hash;
        assert(current_hash >= 0);
    }

    cout << "The number of times the pattern has occured in the string is " << count_occurence << '\n';
}

// ABABABAB ABA