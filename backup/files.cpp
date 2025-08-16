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

ostream& operator<<(ostream &os, const pair<int, int> &values) {
    return os << values.first << ' ' << values.second;
}

template<typename T_vector>
void output_vector(T_vector &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << '\n';
    }
}

template<typename Type>
void output_matrix(vector<vector<Type>> &matrix, bool add_one = false) {
    int row = matrix.size(), column = matrix[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << matrix[i][j] + add_one << ' ';
        }

        cout << '\n';
    }
}

int main() {
    int n = rand();
    // cin >> n;
    vector<int> numbers(n);
    vector<pair<int, int>> sorted_frequency;
    unordered_map<int, int> frequency;

    string name = "sourav auddy";
    stringstream in(name);
    int counter = 0;

    vector<string> words;
    while (in >> name) {
        words.push_back(name);
        counter++;
    }

    output_vector(words);

    cout << counter << '\n';
    return 0;

    for (int &number : numbers)
        cin >> number;

    for (int number : numbers)
        frequency[number]++;

    for (auto freq : frequency) {
        sorted_frequency.emplace_back(freq.first, freq.second);
    }

    vector<pair<int, int>> prefix_sums = sorted_frequency;

    for (int i = 1; i < sorted_frequency.size(); i++) {
        prefix_sums[i].second = prefix_sums[i].second + prefix_sums[i - 1].second;
    }

    cout << "The  frequency table is " << '\n';
    output_vector(sorted_frequency);

    cout << "The prefix sums frequency table is " << '\n';
    output_vector(prefix_sums);
}