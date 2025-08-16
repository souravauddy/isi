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

#define debug(x) cout << #x << " = " << x << '\n'


template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false, int end = -1) {
    int n = end;
    
    if (end == -1) 
        n = numbers.size() - 1;
        
    for (int i = 0; i < end; i++) {
        cout << numbers[i] + add_one << "\n "[i + 1 < n];
    }
}

int counter = 0;

void partitions(vector<int> &parts, int number, int current = 1, int index = 0, int sum = 0) {
    if (sum > number)
        return;
    
    if (sum == number) {
        counter++;
        // output_vector(parts, false, current - 1);
        return;
    }
    
    for (int i = current; i <= number - sum; i++) {
        parts[index] = i;
        partitions(parts, number, i, index + 1, sum + i);
    }
}

int main() {
    int number;
    cin >> number;
    vector<int> parts(number);

    for (int part : parts) 
        cout << part << '\n';
    
    partitions(parts, number);

    cout << counter << '\n';
}