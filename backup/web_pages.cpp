#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <vector>

constexpr const int INF = int(1e9 + 5);

int main() {
    int M1, M2, N;
    std::cin >> M1 >> M2 >> N;
    std::vector<int> village(N);
    
    for (int &people : village)
        std::cin >> people;
        
    int64_t total_sum = std::accumulate(village.begin(), village.end(), 0LL);
    int64_t answer = INF;
    std::map<int, bool> cache;
    
    std::function<void(int, int)> recurse = [&](int index, int sum) -> void {
        answer = std::min(answer, std::max<int64_t>(sum * M1, (total_sum - sum) * M2));
        answer = std::min(answer, std::max<int64_t>(sum * M2, (total_sum - sum) * M1));
        
        if (index == N)
            return;
            
        if (cache.find(sum) != cache.end())
            return;
            
        recurse(index + 1, sum);
        recurse(index + 1, sum + village[index]);
        cache[sum] = true;
    };
    
    recurse(0, 0);
    
    std::cout << answer << '\n';
}