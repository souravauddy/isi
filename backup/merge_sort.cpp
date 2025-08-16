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

void merge(vector<int> &numbers, int low, int high, int mid) {
    vector<int> sorted(high - low + 1); 
    int k = 0, i = low, j = mid + 1;

    while (i <= mid && j <= high) {
        if (numbers[i] < numbers[j]) {
            sorted[k++] = numbers[i++];
        } else {
            sorted[k++] = numbers[j++];
        }
    }

    while (i <= mid) 
        sorted[k++] = numbers[i++];
    
    while (j <= high)
        sorted[k++] = numbers[j++];

    k = 0;
    for (int i = low; i <= high; i++) {
        numbers[i] = sorted[k++]; 
    }
}

void merge_sort(vector<int> &numbers, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort(numbers, low, mid);
        merge_sort(numbers, mid + 1, high);
        merge(numbers, low, high, mid);
    }
}

int main() {
    cout << "Enter the size of the numbers" << '\n';
    int size;
    cin >> size;
    vector<int> numbers(size);

    cout << "Enter the numbers" << '\n';
    for (int &number : numbers)
        cin >> number;

    merge_sort(numbers, 0, size - 1);

    cout << "The sorted numbers are" << '\n';
    for (int number : numbers)
        cout << number << ' ';
    cout << '\n';
}

/*
5
300 9 294 324 5
9 300       5 294 324
  |                |


5 9 294 300 324

*/