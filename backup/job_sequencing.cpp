// #include <bits/stdc++.h>
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
#include <atomic>

using namespace std;

#define debug(x) std::cerr << #x << " = " << x << '\n'

const char NULL_CHAR = '\0';

struct Job {
    char id;
    bool used;
    int profit, deadline;

    Job(char _id = NULL_CHAR, bool _used = false, int _profit = 0, int _deadline = 0) : id(_id), used(_used), profit(_profit), deadline(_deadline) {}

    bool operator<(const Job &other) const {
        return deadline < other.deadline;
    }
};

void best_sequence(std::vector<Job> &jobs) {
    int size = max_element(jobs.begin(), jobs.end())->deadline;
    std::vector<Job> schedule(size);
    std::vector<bool> used(size + 1, false);
    int total = 0;

    auto get_slot = [&](const Job &job) -> int {
        for (int slot = size; slot >= 0; slot--) {
            if (slot < job.deadline && !used[slot])  {
                used[slot] = true;
                return slot;
            }
        }

        return -1;  // there exists no slot for that job 
    };

    for (const auto &job : jobs) {
        int slot = get_slot(job);

        if (slot != -1)
            schedule.push_back(job);
    }

    std::cout << '\n' << "The job sequence is " << '\n';

    for (const auto &job : schedule) {
        total += job.profit;
        std::cout << job.id << " " << job.profit << '\n';
    }

    std::cout << "The total profit is = " << total << '\n';
}

int main() {
    int N;
    std::cin >> N;
    std::vector<Job> jobs(N);
    
    for (auto &job : jobs)
        std::cin >> job.id >> job.deadline >> job.profit;

    std::stable_sort(jobs.begin(), jobs.end(), [&](Job &a, Job &b) {
        return a.profit > b.profit;
    });

    best_sequence(jobs);
}

/*
4
A 2 100
B 1 15
C 2 25
D 1 40
// E 1 100
*/