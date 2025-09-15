#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <iomanip>
#include <cassert>

// using namespace std;

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
    std::cerr << std::endl;
}

template<typename Type>
std::ostream& operator<<(std::ostream &os, const std::vector<Type> &other) {
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
    std::cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

const double SENTINEL = double(1e9 + 7);
const double EPSILON = double(1e-6);

inline int compare(double x, double y) {
    if (fabs(x - y) < EPSILON)
        return 0;

    return x - y > 0 ? 1 : -1;
}

inline bool equal(double x, double y) {
    return compare(x, y) == 0;
}

inline int compare(std::array<double, 2> &interval1, std::array<double, 2> &interval2) {
    if (equal(interval1[0], interval2[0]) && equal(interval1[1], interval2[1]))
        return 0;

    // returns -1 when interval1 > interval2
    return interval1[0] > interval2[1] ? -1 : 1;
}

inline bool greater(std::array<double, 2> &interval1, std::array<double, 2> &interval2) {
    return compare(interval1, interval2) == -1;
}

inline bool less(std::array<double, 2> &interval1, std::array<double, 2> &interval2) {
    return compare(interval1, interval2) == 1;
}

inline bool greater_equal(double x, double y) {
    return compare(x, y) != -1;
}

inline bool less_equal(double x, double y) {
    return compare(x, y) != 1;
}

struct function {
    std::vector<std::array<double, 2>> intervals;

    void add_interval(double x, double y) {
        intervals.push_back({x, y});
    }

    [[nodiscard]]
    std::array<double, 2>& operator[](unsigned int index) {
        return intervals.at(index);
    }

    void swap(function &other) {
        this->intervals.swap(other.intervals);
    }

    [[nodiscard]]
    unsigned int size() {
        return intervals.size();
    }

    void join_intervals() {
        std::vector<std::array<double, 2>> joined_intervals{intervals[0]};

        for (int i = 1, j = 0; i < intervals.size(); i++) {
            if (equal(joined_intervals[j][1], intervals[i][0])) {
                joined_intervals[j][1] = intervals[i][1];
            } else if (joined_intervals[j][1] < intervals[i][0]) {
                joined_intervals.push_back(intervals[i]);
                j++;
            } else {
                joined_intervals[j][1] = std::max(joined_intervals[j][1], intervals[i][1]);
            }
        }

        this->intervals = std::move(joined_intervals);
    }
};

void read_function(function &func, int N) {
    for (int i = 0; i < N; i++) {
        double x, y;
        std::cin >> x >> y;
        assert(x <= y);
        func.add_interval(x, y);
    }
}

bool intersecting_interval(std::array<double, 2> &interval1, std::array<double, 2> &interval2) {
    return interval1[1] < interval2[0] || interval2[1] < interval1[0] ? false : true;
}

std::array<double, 2> find_largest_interval(function &f, function &g) {
    bool interval_found = false;
    double max_interval_start, max_interval_end;
    double x = f[0][0], y = g[0][0];
    int pointer1 = 0, pointer2 = 0;

    while (pointer1 < f.size() && pointer2 < g.size()) {
        if (intersecting_interval(f[pointer1], g[pointer2])) {
            double interval_start = std::max(f[pointer1][0], g[pointer2][0]), interval_end = std::min(f[pointer1][1], g[pointer2][1]);

            if (interval_end - interval_start > max_interval_end - max_interval_start) {
                max_interval_start = interval_start;
                max_interval_end = interval_end;
            }

            interval_found = true;
            pointer1++;
            continue;
        }

        if (greater(f[pointer1], g[pointer2])) {
            pointer2++;
            continue;
        }
        
        pointer1++;
    }

    if (!interval_found)
        return {SENTINEL, SENTINEL};
    
    return {max_interval_start, max_interval_end};
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int M, N;
    function f, g;

    std::cin >> M;
    read_function(f, M);
    std::cin >> N;
    read_function(g, N);

    f.join_intervals();
    g.join_intervals();

    auto [x, y] = find_largest_interval(f, g);

    if (x == SENTINEL && y == SENTINEL) {
        std::cout << "None" << '\n';
        return 0;
    }

    std::cout << std::fixed << std::setprecision(6) << x << ' ' << y << '\n';
    std::cout << y - x << '\n';
}
