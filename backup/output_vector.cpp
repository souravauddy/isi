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
void output_vector(const std::vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

template<typename Type>
void output_matrix(std::vector<std::vector<Type>> &matrix, int start = 0) {
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = start; i < row; i++) 
        for (int j = start; j < column; j++) 
            std::cout << std::setw(4) << (matrix[i][j]) << " \n"[j + 1 == column];
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);

    for (int &x : numbers)
        cin >> x;

    output_vector(numbers);
}