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

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

void debug_out() {
    cerr << endl;
}

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) 
        os << other[i] << ", ";
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

struct rectangle {
    int64_t height, width;

    rectangle(int64_t _height = 0, int64_t _width = 0) : height(_height), width(_width) {}

    bool operator<(const rectangle &other) const {
        return height == other.height ? area(*this) < area(other) : height < other.height;
    }

    static int64_t area(const rectangle &rectangle) {
        return rectangle.height * rectangle.width;
    }
};

void run_case() {
    int N, Q;
    cin >> N >> Q;
    vector<rectangle> rectangles(N);

    for (auto &rectangle : rectangles)
        cin >> rectangle.height >> rectangle.width;

    sort(rectangles.begin(), rectangles.end());

    vector<int64_t> prefix_sum_area(N, 0);

    prefix_sum_area[0] = rectangle::area(rectangles[0]);

    for (int i = 1; i < N; i++)
        prefix_sum_area[i] = prefix_sum_area[i - 1] + rectangle::area(rectangles[i]);

    int low = 0, high = N - 1;

    for (int q = 0; q < Q; q++) {
        int hs, ws, hb, wb;
        cin >> hs >> ws >> hb >> wb;
        
        int l = int(upper_bound(rectangles.begin(), rectangles.end(), hs) - rectangles.begin());
        int r = int(lower_bound(rectangles.begin(), rectangles.end(), hb) - rectangles.begin());

        while (r >= 0 && rectangles[r].height == hb)
            r--;

        while (l < N && rectangles[l].height == hs)
            l++;

        
    }
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}