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
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define debug(x) cerr << #x << " = " << x << '\n'

const int INF = int(1e9 + 5);

struct edge {
    int destination, weight;

    edge(int _destination = 0, int _weight = INF) : destination(_destination), weight(_weight) {}
};

struct node {
    int vertex, weight;

    node(int _vertex = 0, int _weight = INF) : vertex(_vertex), weight(_weight) {}

    bool operator<(const node &other) const {
        return weight < other.weight;
    }

    bool operator>(const node &other) const {
        return weight > other.weight;
    }

    bool operator<=(const node &other) const {
        return weight <= other.weight;
    }

    bool operator>=(const node &other) const {
        return weight >= other.weight;
    }

    friend ostream& operator<<(ostream &os, const node &other) {
        return os << other.vertex << ' ' << other.weight;
    }
};

template<typename Type>
class PriorityQueue {
    vector<Type> heap;
    vector<int> position;
    const int TOP = 1;
    int size = 0;

    static int left_child(int parent) {
        return 2 * parent;
    }

    static int right_child(int parent) {
        return 2 * parent + 1;
    }

    static int parent(int child) {
        return child / 2;
    }
    
    void heapify(int parent) {
        if (left_child(parent) > size && right_child(parent) > size)
            return;

        int child = parent;
        
        if (left_child(parent) <= size && heap[parent] >= heap[left_child(parent)]) 
            child = left_child(parent);
        if (right_child(parent) <= size && heap[child] >= heap[right_child(parent)]) 
            child = right_child(parent);

        if (child == parent)
            return;

        swap(heap[parent], heap[child]);
        swap(position[heap[parent].vertex], position[heap[child].vertex]);

        heapify(child);
    }

    void up_heapify(int index) {
        for (int child = index; parent(child) > 0; child = parent(child)) {
            if (heap[child] < heap[parent(child)]) {
                swap(heap[child], heap[parent(child)]);
                swap(position[heap[child].vertex], position[heap[parent(child)].vertex]);
            }
        }
    }

public:

    PriorityQueue(int size) {
        heap.resize(size + 1);
        position.resize(size);
        iota(position.begin(), position.end(), 1);
        this->size = size + 1;
    }

    PriorityQueue(const vector<Type> &other) {
        heap = other;
        heap.push_back({0, INF});
        position.resize(other.size());
        iota(position.begin(), position.end(), 1);
        this->size = other.size() + 1;
    }

    Type top() {
        Type minimum = heap[TOP];
        
        swap(heap[TOP], heap[size - 1]);
        heap.pop_back();
        size -= 2;
        heapify(TOP);
        size++;

        return minimum;
    }

    void reset() {
        iota(position.begin(), position.end(), 1);
    }

    void update(const int vertex, const int weight) {
        heap[position[vertex]].weight = weight;
        heap[position[vertex]].vertex = vertex;
        up_heapify(position[vertex]);
    }

    int weight(int vertex) {
        return heap[position[vertex]].weight;
    }

    bool empty() {
        return size == 1;
    }

    void print_nodes() {
        for (int i = 1; i < heap.size(); i++) {
            cout << heap[i].vertex << " " << heap[i].weight << '\n';
        }
    }

    void print_positions() {
        for (int i = 0; i < position.size(); i++) {
            cout << i << " " << position[i] << '\n';
        }
    }

    int heap_size() {
        return this->size;
    }
};

void print_list(vector<vector<edge>> &adjacency_list) {
    int vertices = adjacency_list.size();

    for (int vertex = 0; vertex < vertices; vertex++) {
        cout << "For vertex: " << vertex << ": " << '\n';
        
        for (auto node : adjacency_list[vertex]) {
            cout << node.destination << " " << node.weight << '\n';
        }
    }
}

template<typename Type>
void output_vector(vector<Type> &numbers, bool plus_one = false) {
    for (auto number : numbers)
        cout << number + plus_one << ' ';
    cout << '\n';
}

void prims_spanning_tree(vector<vector<edge>> &adjacency_list, PriorityQueue<node> &heap, int source) {
    int vertices = adjacency_list.size();
    vector<bool> used(vertices, false);
    vector<int> parent(vertices, source);

    cout << "The paths are" << '\n';

    while (!heap.empty()) {
        node minimum = heap.top();
        int vertex = minimum.vertex;
        used[vertex] = true;

        if (parent[vertex] != vertex)
            cout << parent[vertex] << ' ' << vertex << '\n';

        for (int i = 0; i < adjacency_list[vertex].size(); i++) {
            edge current = adjacency_list[vertex][i];

            if (!used[current.destination] && current.weight < heap.weight(current.destination)) {
                heap.update(current.destination, current.weight);
                parent[current.destination] = vertex;
            }
        }
    }
}

int main() {
    int edges, vertices;
    cout << "Enter the number of vertices and the number of edges" << '\n';
    cin >> vertices >> edges;

    vector<vector<edge>> adjacency_list(vertices);

    cout << "Enter the adjacency list" << '\n';
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;

        adjacency_list[u].emplace_back(v, weight);
        adjacency_list[v].emplace_back(u, weight);
    }

    cout << "Enter the source vertex" << '\n';
    int source;
    cin >> source;

    PriorityQueue<node> heap(vertices);

    for (int i = 0; i < vertices; i++) 
        heap.update(i, INF);
    heap.update(source, 0);

    heap.reset();

    prims_spanning_tree(adjacency_list, heap, source);
}

/*
5 7
0 1 10
0 4 20
1 2 30
1 3 40
1 4 50
2 3 60
3 4 70
0 

9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14 
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
0
*/