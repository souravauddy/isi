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
        os << other[i] << ", ";
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif
    
    int N;
    cin >> N;
    vector<int> numbers(N);

    for (int &number : numbers)
        cin >> number;

    int required_sum;
    cin >> required_sum;
    vector<int> combination;
    int combination_count = 0;

    y_combinator([&](auto self, int sum, int index, vector<int> &combination) -> void {
        /*
            simple solution with O(n!) complexity to print all the combinations, 
            but answer can contain duplicates, 
            so you can first run sort and then unique the array to get rid of the duplicates.
        */
        if (sum == required_sum) {
            debug(combination);
            combination_count++;
            return;
        }

        for (int i = index + 1; i < N; i++) {
            if (sum + numbers[i] <= required_sum) {
                combination.push_back(numbers[i]);
                self(sum + numbers[i], i, combination);
                combination.pop_back();
            }
        }
    })(0, -1, combination);

    assert(combination.empty());
    debug(combination_count);
}

/*
input:
5
-3 -2 5 2 3
5
*/