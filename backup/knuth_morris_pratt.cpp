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

int main() {
    string sentence, pattern;
    cin >> sentence >> pattern;
    const int N = int(sentence.length());
    const int M = int(pattern.length());
    vector<int> proper_prefix_length(M, 0);
    int common_suffix_length = 0;

    for (int i = 1; i < M; i++) {       // computing the proper prefix array
        if (pattern[common_suffix_length] == pattern[i]) {
            proper_prefix_length[i] = ++common_suffix_length;
        } else {
            if (pattern[max(common_suffix_length - 1, 0)] == pattern[i]) {
                proper_prefix_length[i] = common_suffix_length;
            } else {
                proper_prefix_length[i] = common_suffix_length = 0;
            }
        }
    }

    int pattern_index = 0, count_occurence = 0;
    int index = 0;

    while (index < N) {
        if (sentence[index] == pattern[pattern_index]) {
            index++, pattern_index++;
        } else {
            if (pattern_index == 0) {
                index++;
                continue;
            }

            pattern_index = proper_prefix_length[pattern_index - 1];
        }

        if (pattern_index == M) {
            count_occurence++;
            pattern_index = proper_prefix_length[pattern_index - 1];
        }
    }

    cout << "The number of times the pattern is present in the sentence is " << count_occurence << '\n';
}

// ACACAGACACAGA ACACAGA
// ABABABAB AB
// AAAAABAAABA AAAA