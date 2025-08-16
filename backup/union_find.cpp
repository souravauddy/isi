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
#include <set>
#include <unordered_set>
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
void output_vector(T_vector &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

struct union_find {  // union find using rank and path compression, only valid for un-directed graphs
    vector<int> parent;
    vector<int> rank;
    int components = 0;

    union_find(int size) {
        parent.assign(size + 1, 0);
        rank.assign(size + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int vertex) {
        if (parent[vertex] == vertex)
            return vertex;
        return parent[vertex] = find(parent[vertex]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) 
            return false;

        if (rank[a] < rank[b])
            swap(a, b); 

        parent[b] = parent[a];
        rank[a] += rank[b];
        components++;

        return true;
    }

    bool same_set(int a, int b) noexcept {
        return find(a) == find(b);
    }

    int count() const {
        return parent.size() - components - 1;  // since we are taking +1 on the size we are doing -1
    }
};  

int main() {
    int M, N;
    std::cin >> M >> N;
    std::vector<std::array<int, 2>> edges(M);
    std::set<int> planets;

    for (int i = 0; i < M; i++)
        std::cin >> edges[i][0] >> edges[i][1];

    for (int i = 0; i < M; i++) {
        union_find UF(N);
        
        for (int j = 0; j < M; j++)
            if (i != j)
                UF.unite(edges[j][0], edges[j][1]);

        if (UF.count() != 1)
            planets.insert(edges[i][0]), planets.insert(edges[i][1]);
    }

    if (planets.empty()) {
        std::cout << -1 << '\n';
        return 0;
    }

    for (int planet : planets)
        std::cout << planet << ' ';
    std::cout << '\n';
}
