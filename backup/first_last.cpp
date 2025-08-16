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
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int N;
    cin >> N;
    vector<int> numbers(N);

    for (int &number : numbers)
        cin >> number;

    int target;
    cin >> target;
    int first = -1, last = -1;
    int low = 0, high = N - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (numbers[mid] < target) {
            low = mid + 1;
        } else {
            first = mid;
            high = mid - 1;
        }
    }

    if (numbers[first] != target) {
        cout << "There are no occurence" << '\n';
        return 0;
    }

    low = 0, high = N - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (numbers[mid] <= target) {
            last = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    assert(numbers[first] == target && numbers[last] == target);
    cout << last - first + 1 << '\n';
}

/*
5
2 4 4 5 5
5
*/