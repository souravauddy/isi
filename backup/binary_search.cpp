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

// this works fine upto 5 digits of precision, own implementation

using namespace std;

const float EPSILON = 1e-5;

int main() {
    int number;
    cin >> number;

    int low = 0, high = number;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (mid * mid == number) {
            cout << mid << '\n';
            return 0;
        } else if (mid * mid < number) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << fixed << EPSILON << '\n';
    float float_number = (float) number;
    float float_low = (float) low;
    float float_high = (float) high;

    cout << setprecision(8) << sqrt(number) << '\n';
    // cout << low << " " << high << '\n';
    swap(float_low, float_high);
    
    while (float_high >= float_low && float_high / float_low > EPSILON) {
        float mid = float_low + (float_high - float_low) / 2;

        if (mid * mid == float_number) {
            cout << mid << '\n';
            return 0;
        } else if (mid * mid <= number) {
            float_low = mid + EPSILON;
        } else {
            float_high = mid - EPSILON;
        }
    }

    cout << setprecision(8) << float_low << '\n';
}