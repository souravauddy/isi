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
    cout << "Enter the number of elements in the array" << '\n';
    int size;
    cin >> size;
    vector<int> numbers(size);

    cout << "Enter the elements in the array" << '\n';
    for (int &number : numbers)
        cin >> number;

    cout << "Enter the value to be searched" << '\n';
    int target;
    cin >> target;

    auto index = y_combinator([&](auto binary_search, int low, int high) -> int {
        if (low <= high) {
            int mid = low + (high - low) / 2;

            if (numbers[mid] == target)
                return mid;
            else if (numbers[mid] < target) 
                return binary_search(mid + 1, high);
            else    
                return binary_search(low, mid - 1);
        }

        return -1;
    })(0, size - 1);

    if (~index)
        cout << "The value is present at " << index + 1 << '\n';
    else 
        cout << "The value is not present in the array" << '\n';
}
