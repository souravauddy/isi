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

template<typename T_vector>
void output_vector(T_vector &numbers, bool add_one = false, int start = -1, int end = -1) {
    if (start < 0) start = 0;
    if (end < 0) end = numbers.size() - 1;
    for (int i = start; i <= end; i++) {
        cout << numbers[i] + add_one << " \n"[i == end];
    }
}

int left_child(int parent) {
    return 2 * parent;
}

int right_child(int parent) {
    return 2 * parent + 1;
}

int parent(int child) {
    return child / 2;
}

const int TOP = int(1);

int main() {
    cout << "Enter the size of the array" << '\n';
    int size;
    cin >> size;
    vector<int> numbers(size + 1);
    vector<int> &heap = numbers;
    int another_size = size;

    cout << "Enter the elements of the array" << '\n';
    for (int i = 1; i <= size; i++)
        cin >> numbers[i];

    auto heapify = y_combinator([&](auto self, int parent) -> void {
        if (left_child(parent) > size && right_child(parent) > size)
            return;

        int child = parent;

        if (left_child(parent) <= size && heap[parent] <= heap[left_child(parent)]) 
            child = left_child(parent);
        if (right_child(parent) <= size && heap[child] <= heap[right_child(parent)]) 
            child = right_child(parent);

        if (child == parent)
            return;

        swap(heap[parent], heap[child]);

        self(child);
    });

    while (size > 1) {
        for (int child = size; parent(child) > 0; child = parent(child))
            if (heap[child] > heap[parent(child)]) 
                swap(heap[child], heap[parent(child)]);
        
        size--;
    }

    size = another_size;

    while (size > 1) {  
        swap(heap[TOP], heap[size]);
        size--;
        heapify(TOP);
    }

    cout << "The sorted array is" << '\n';
    output_vector(numbers, false, 1);
}