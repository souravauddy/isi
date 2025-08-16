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

    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (numbers[mid] == value) {
            cout << "value found at " << mid + 1 << '\n';
            return 0;
        } else if (numbers[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    

    cout << "The value is not present in the array" << '\n';
}