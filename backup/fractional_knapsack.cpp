#include <iostream>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>

using namespace std;

#define debug(x) cerr << #x << " = " << x << '\n'

struct Item {
    int price, weight;

    Item(int _price = 0, int _weight = 0) : price(_price), weight(_weight) {}
    
    bool operator<(const Item &other) {
        return price < other.price;
    }
};

int main() {
    int size;
    cin >> size;
    vector<Item> items(size);
    vector<pair<float, int>> profit_per_unit(size);

    for (auto &item : items) {
        cin >> item.price >> item.weight;
    }

    for (int i = 0; i < size; i++) {
        profit_per_unit[i].first = (float) items[i].price / items[i].weight;
        profit_per_unit[i].second = items[i].weight;
    }

    sort(profit_per_unit.rbegin(), profit_per_unit.rend());

    int capacity;
    cin >> capacity;
    double profit = 0;

    for (int i = 0; capacity > 0 && i < size; i++) {
        if (profit_per_unit[i].second <= capacity) {
            profit += (profit_per_unit[i].first * profit_per_unit[i].second);
            capacity -= profit_per_unit[i].second;
        } else {
            profit += capacity * profit_per_unit[i].first;
            break;
        }
    }

    cout << "The maximum profit is: " << profit << '\n';
}

/*
7
5 1
10 3
15 5
7 4
8 1
9 3
4 2
15

*/