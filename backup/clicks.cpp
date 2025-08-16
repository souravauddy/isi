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
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <memory>

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

const int INF = int(1e9 + 5);

inline int count_digits(int number) {
    return int(log10(number) + 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int lowest, highest;
    std::cin >> lowest >> highest;
    int B;
    std::cin >> B;
    std::unordered_set<int> banned;

    for (int b = 0; b < B; b++) {
        int channel;
        std::cin >> channel;
        banned.insert(channel);
    }

    int V;
    std::cin >> V;
    std::vector<int> view(V);

    for (int &channel : view)
        std::cin >> channel;

    int last_channel = INF;

    auto evaluate_clicks_smaller = [&](const int current_channel, const int destination_channel) -> std::pair<int, int> {
        int smaller_clicks = 0, digits = count_digits(destination_channel);

        for (int channel = current_channel; channel >= lowest && smaller_clicks < digits; channel--) {
            if (banned.find(channel) != banned.end())
                continue;

            smaller_clicks++;

            if (channel == destination_channel)
                break;
        }

        int greater_clicks = 0;

        for (int channel = current_channel; channel <= highest && greater_clicks < digits; channel++) {
            if (banned.find(channel) != banned.end())
                continue;

            greater_clicks++;

            if (channel == destination_channel)
                break;
        }

        return {smaller_clicks, greater_clicks};
    };

    auto evaluate_clicks_greater = [&](const int current_channel, const int destination_channel) -> std::pair<int, int> {
        int smaller_clicks = 0;
        int digits = count_digits(destination_channel);

        for (int channel = current_channel; channel <= highest && smaller_clicks < digits; channel++) {
            if (banned.find(channel) != banned.end())
                continue;

            smaller_clicks++;

            if (channel == destination_channel)
                break;
        }

        int greater_clicks = 0;

        for (int channel = current_channel; channel >= lowest && greater_clicks < digits; channel--) {
            if (banned.find(channel) != banned.end())
                continue;

            greater_clicks++;

            if (channel == destination_channel)
                break;
        }

        return {smaller_clicks, greater_clicks};
    };

    auto evaluate_clicks = [&](const int current_channel, const int destination_channel) -> int {
        auto [up_click, down_click] = destination_channel > current_channel ? evaluate_clicks_greater(current_channel, destination_channel) : evaluate_clicks_smaller(current_channel, destination_channel);
        return std::min(up_click, down_click);
    };

    int answer = std::min(count_digits(view.front()), evaluate_clicks(lowest, view.front()));

    for (int v = 1; v < V; v++)
        answer += std::min({count_digits(view[v]), evaluate_clicks(view[v - 1], view[v]), v - 2 >= 0 && view[v - 2] == view[v] ? 1 : INF});

    std::cout << answer << '\n';
}
