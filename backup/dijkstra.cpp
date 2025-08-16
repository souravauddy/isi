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

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

const int INF = int(1e9 + 5);

struct Edge {
    int edge, weight;

    Edge(int _edge = 0, int _weight = INF) : edge(_edge), weight(_weight) {}
};

struct Node : public Edge {
    int vertex, weight;

    Node(int _vertex = 0, int _weight = INF) : vertex(_vertex), weight(_weight) {}

    bool operator<(const Node &other) const {
        return weight < other.weight;
    }

    bool operator>(const Node &other) const {
        return weight > other.weight;
    }

    bool operator<=(const Node &other) const {
        return weight <= other.weight;
    }

    bool operator>=(const Node &other) const {
        return weight >= other.weight;
    }

    friend ostream& operator<<(ostream &os, const Node &other) {
        return os << other.vertex << ' ' << other.weight;
    }
};

template<typename Type>
class PriorityQueue {
    vector<Type> heap;
    vector<int> position;
    static const int TOP = 1;
    int size = 0;

    int left_child(int parent) const {
        return 2 * parent;
    }

    int right_child(int parent) const {
        return 2 * parent + 1;
    }

    int parent(int child) const {
        return child / 2;
    }
    
    void heapify(int parent) noexcept {
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

    void up_heapify(int index) noexcept {
        for (int child = index; parent(child) > 0; child = parent(child)) {
            if (heap[child] < heap[parent(child)]) {
                swap(heap[child], heap[parent(child)]);
                swap(position[heap[child].vertex], position[heap[parent(child)].vertex]);
            }
        }
    }

public:

    PriorityQueue(int size) noexcept {
        heap.resize(size + 1);
        position.resize(size);
        iota(position.begin(), position.end(), 1);
        this->size = size + 1;
    }

    PriorityQueue(const vector<Type> &other) noexcept {
        heap = other;
        heap.push_back({0, INF});
        position.resize(other.size());
        iota(position.begin(), position.end(), 1);
        this->size = other.size() + 1;
    }

    Type top() noexcept {
        Type minimum = heap[TOP];
        
        swap(heap[TOP], heap[size - 1]);
        heap.pop_back();
        size -= 2;
        heapify(TOP);
        size++;

        return minimum;
    }

    void reset() noexcept {
        iota(position.begin(), position.end(), 1);
    }

    void update(const int vertex, const int weight) noexcept {
        heap[position[vertex]].weight = weight;
        heap[position[vertex]].vertex = vertex;
        up_heapify(position[vertex]);
    }

    int weight(int vertex) const {
        return heap[position[vertex]].weight;
    }

    bool empty() const {
        return size == 1;
    }

    void print_nodes() const {
        for (int i = 1; i < heap.size(); i++) {
            cout << heap[i].vertex << " " << heap[i].weight << '\n';
        }
    }

    void print_positions() const {
        for (int i = 0; i < position.size(); i++) {
            cout << i << " " << position[i] << '\n';
        }
    }

    int heap_size() noexcept {
        int heap_size = this->size;
        return heap_size;
    }
};

void dijkstra(vector<vector<Edge>> &adjacency_list) {
    int source, vertices = adjacency_list.size();
    cin >> source;

    vector<bool> visited(vertices, false);
    vector<int> distance(vertices, INF);
    PriorityQueue<Node> heap(vertices); // this is a min heap
    distance[source] = 0;

    for (int i = 0; i < vertices; i++)
        heap.update(i, INF);

    heap.update(source, 0);
    heap.reset();

    while (!heap.empty()) {
        Node minimum = heap.top();
        int vertex = minimum.vertex;    
        visited[vertex] = true;

        for (int i = 0; i < adjacency_list[vertex].size(); i++) {
            Edge current = adjacency_list[vertex][i];

            if (!visited[current.edge] && distance[current.edge] > distance[vertex] + current.weight) {
                distance[current.edge] = distance[vertex] + current.weight;
                heap.update(current.edge, distance[vertex] + current.weight);
            }
        }
    }

    cout << "The distance vertex is :" << '\n';
    output_vector(distance);
}

void print_list(vector<vector<Edge>> &adjacency_list) {
    int vertices = adjacency_list.size();

    for (int vertex = 0; vertex < vertices; vertex++) {
        cout << "For vertex: " << vertex << ": " << '\n';
        
        for (auto node : adjacency_list[vertex]) {
            cout << node.edge << " " << node.weight << '\n';
        }
    }
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;
    vector<vector<Edge>> adjacency_list(vertices);

    for (int i = 0; i < edges; i++) {
        int u, v, weight;   
        cin >> u >> v >> weight;

        adjacency_list[v].emplace_back(u, weight);
        adjacency_list[u].emplace_back(v, weight);
    }

    dijkstra(adjacency_list);
}

/*
3 3
0 1 3
1 2 4
2 0 -9
0

9 14
0 1  4
0 7  8
1 2  8
1 7 11
2 3  7
2 8  2
2 5  4
3 4  9
3 5 14
4 5 10
5 6  2
6 7  1
6 8  6
7 8  7
0
*/

// tumi ekbar leave kore join koro 

/*
    amar side er problem mone hoi
    
*/
