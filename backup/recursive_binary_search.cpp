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

bool binary_search(vector<int> &numbers, int low, int high, int value) {
    if (low <= high) {
        int mid = low + (high - low) / 2;

        if (numbers[mid] == value) {
            cout << "The value is found at " << mid + 1 << '\n';
            return true;
        } else if (numbers[mid] < value) {
            return binary_search(numbers, mid + 1, high, value);
        } else {
            return binary_search(numbers, low, mid - 1, value);
        }
    }

    return false;
}

int main() {
    cout << "Enter the size of the array" << '\n';
    int size;
    cin >> size;
    vector<int> numbers(size);

    cout << "Enter the array elements" << '\n';
    for (int &number : numbers)
        cin >> number;

    cout << "Enter the value to be searched" << '\n';
    int value;
    cin >> value;

    if (!binary_search(numbers, 0, size - 1, value))
        cout << "The value is not present in the array" << '\n';
}