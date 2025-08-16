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

const int INF = int(1e9 + 5);

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    int vertices;
    cin >> vertices;
    vector<vector<int>> adjacency_matrix(vertices, vector<int>(vertices, 0));

    for (int i = 0; i < vertices; i++) 
        for (int j = 0; j < vertices; j++) {
            cin >> adjacency_matrix[i][j];

            if (i != j && adjacency_matrix[i][j] == 0) 
                adjacency_matrix[i][j] = INF;
        }

    vector<int> path(vertices, 0);
    vector<int> best_path;
    int best = INF;
    iota(path.begin(), path.end(), 0);

    auto get_cost = [&](vector<int> &path) -> int {
        path.push_back(0);
        int cost = 0;

        for (int i = 0; i < vertices; i++) 
            cost += adjacency_matrix[path[i]][path[i + 1]];
        path.pop_back();

        return cost;
    };
    
    y_combinator([&](auto self, vector<int> &permutation, int index) -> void {
        if (index == vertices) {
            int cost = get_cost(permutation);

            if (cost < best) {
                best_path = permutation;
                best = cost;
            }

            return;
        }
        
        for (int i = index; i < vertices; i++) {
            swap(permutation[index], permutation[i]);
            self(permutation, index + 1);
            swap(permutation[index], permutation[i]);
        }
    })(path, 0);

    best_path.push_back(0);
    output_vector(best_path);

    

    cout << "The best possible cost is " << best << '\n';
}