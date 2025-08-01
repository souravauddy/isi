#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int number_of_factors(int number) {
    int count = 0;

    for (int factor = 1; factor * factor <= number; factor++)
        if (number % factor == 0)
            count++;

    return count;
}

int main() {
    int N;
    scanf("%d", &N);
    bool *bulbs = (bool *) malloc(N * sizeof(bool));

    for (int i = 0; i < N; i++)
        bulbs[i] = true;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j += i + 1) {
            bulbs[j] ^= true;
        }
    }

    for (int i = 0; i < N; i++)
        printf("%d ", bulbs[i]);
    puts("");
}

/*
0 0
1 1
1 0
*/