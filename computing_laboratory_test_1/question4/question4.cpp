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

struct line {
    double slope, y_intercept;

    line() = default;

    line(double _slope = 0, double _y_intercept = 0) : slope(_slope), y_intercept(_y_intercept) {}

    line(std::array<double, 2> &point1, std::array<double, 2> &point2) {
        slope = (point2[1] - point1[1]) / (point2[0] - point1[0]);
        y_intercept = point1[1] - point1[0] * slope;
    }

    line(double x1, double y1, double x2, double y2) {
        slope = (y2 - y1) / (x2 - x1);
        y_intercept = x2 - x1 * slope;
    }

    static std::array<double, 2> intersection_point(const line &line1, const line &line2) {
        if (line1.slope == line2.slope && line1.y_intercept != line2.y_intercept)
            return {SENTINEL, SENTINEL};

        if (line1.slope == line2.slope && line1.y_intercept == line2.y_intercept)
            return {-SENTINEL, -SENTINEL};
        
        double abscissa = (line2.y_intercept - line1.y_intercept) / (line1.slope - line2.slope);
        double ordinate = abscissa * line1.slope * line1.y_intercept;
        return {abscissa, ordinate};
    }
};

struct function {
    std::vector<line> lines;

    void add_line(double x1, double y1, double x2, double y2) {
        lines.emplace_back(x1, y1, x2, y2);
    }

    void add_line(std::array<double, 2> &point1, std::array<double, 2> &point2) {
        lines.push_back(line(point1, point2));
    }

    line& operator[](unsigned int index) {
        return lines.at(index);
    }

    const line& operator[](const unsigned int index) const {
        return lines.at(index);
    }
};

struct interval_set {
    std::vector<std::array<double, 2>> intervals;

    void add_interval(double x, double y) {
        intervals.push_back({x, y});
    }

    void add_interval(std::array<double, 2> &interval) {
        intervals.push_back(interval);
    }

    [[nodiscard]]
    std::array<double, 2>& operator[](unsigned int index) {
        return intervals.at(index);
    }

    const std::array<double, 2>& operator[](unsigned int index) const {
        return intervals.at(index);
    }

    void swap(interval_set &other) {
        this->intervals.swap(other.intervals);
    }

    [[nodiscard]]
    unsigned int size() {
        return intervals.size();
    }

    void join_intervals() {
        std::vector<std::array<double, 2>> joined_intervals{intervals[0]};

        for (auto [x, y] : intervals) {
            std::cout << x << ' ' << y << '\n';
            
            for (int i = 0; i < (9e8); i++);
        }
        std::cout << '\n';

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

void read_interval(interval_set &set, int N) {
    for (int i = 0; i < N; i++) {
        double x, y;
        std::cin >> x >> y;
        set.add_interval(x, y);
    }
}

bool intersecting_interval(std::array<double, 2> &interval1, std::array<double, 2> &interval2) {
    return interval1[1] < interval2[0] || interval2[1] < interval1[0] ? false : true;
}

void build_function(function &func, interval_set &set, std::array<double, 2> &interval) {
    interval_set function_set;

    for (auto set_interval : set.intervals) {
        if (intersecting_interval(set_interval, interval))
            function_set.add_interval(set_interval);
    }

    function_set.join_intervals();

    for (int i = 1; i < function_set.size(); i++)
        func.add_line(function_set[i - 1], function_set[i]);

    set = std::move(function_set);
}

bool linearly_separable(const function &f, const function &g, const interval_set &set1, const interval_set &set2, const std::array<double, 2> &interval) {
    auto intersecting = [&](const line &line1, const line &line2, int i, int j) -> bool {
        if (set1[i][1] > set2[j][0])
            return false;
        
        if (set2[j][1] < set1[i][0])
            return false;

        std::array<double, 2> region = {std::max(set1[i][0], set2[j][0]), std::min(set1[i][1], set2[j][1])};
        std::array<double, 2> intersection_point = line::intersection_point(line1, line2);

        if (intersection_point[0] == SENTINEL && intersection_point[1] == SENTINEL)
            return false;

        if (intersection_point[0] == -SENTINEL && intersection_point[1] == -SENTINEL)
            return true;

        if (greater_equal(intersection_point[0], region[0]) && less_equal(intersection_point[1], region[1]))
            return true;
        return false;
    };

    for (int i = 0; i < f.lines.size(); i++) {
        for (int j = 0; j < g.lines.size(); j++) {
            if (intersecting(f[i], g[j], i, j)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int M, N;
    function f, g;
    interval_set set1, set2;

    read_interval(set1, M);
    read_interval(set2, N);
    set1.join_intervals();
    set2.join_intervals();

    std::array<double, 2> interval;
    std::cin >> interval[0] >> interval[1];

    build_function(f, set1, interval);
    build_function(g, set2, interval);

    std::cout << (linearly_separable(f, g, set1, set2, interval) ? "SEPARABLE" : "NOT SEPARABLE") << '\n';
}
