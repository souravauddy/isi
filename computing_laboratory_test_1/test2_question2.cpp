#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <string>
#include <map>

int main() {
    int M, N;
    std::cin >> M >> N;
    std::vector<std::vector<int>> matrix(M, std::vector<int>(N, 0));

    for (int m = 0; m < M; m++)
        for (int n = 0; n < N; n++)
            std::cin >> matrix[m][n];

    std::vector<std::pair<int, double>> sorted_film_rankings(N);

    for (int f = 0; f < N; f++) {
        sorted_film_rankings[f].first = f;

        for (int m = 0; m < M; m++)
            sorted_film_rankings[f].second += matrix[m][f];
    }

    for (auto &[film, rating] : sorted_film_rankings) {
        rating /= M;
        std::cout << std::setprecision(2) <<  rating << ' ';
    }

    std::cout << '\n';
    std::cout << std::fixed << std::setprecision(6);

    for (int m = 0; m < M; m++) {
        double MARE = 0;

        for (int n = 0; n < N; n++)
            MARE += fabs(matrix[m][n] - sorted_film_rankings[n].second);
        
        MARE /= N;

        std::cout << MARE << ' ';
    }

    std::cout << '\n';
}
