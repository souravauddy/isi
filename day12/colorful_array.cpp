#include <iostream>
#include <print>
#include <vector>

struct segment {
    int value, left, right;
};

struct segment_tree {
    std::vector<segment> segments;
};

int main() {
    int N;
    std::vector<int> numbers(N, 0);

    segment_tree tree(N);

}