#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

static inline int max(int a, int b) {
    return a > b ? a : b;
}

static inline int64_t max64(int64_t a, int64_t b) {
    return a > b ? a : b;
}

static inline void swap(int * const a, int * const b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int64_t find_maximum_product(int * const numbers, const int size) {
    for (int iter = 0; iter < 3; iter++) {
        for (int i = 0; i < size - iter - 1; i++) {
            if (numbers[i] > numbers[i + 1])
                swap(&numbers[i], &numbers[i + 1]);
        }
    }

    for (int iter = 0; iter < 2; iter++) {
        for (int i = size - 3; i > iter; i--) {
            if (abs(numbers[i]) > abs(numbers[i - 1]))
                swap(&numbers[i], &numbers[i - 1]);
        }
    }

    return max64(1LL * llabs(numbers[0]) * llabs(numbers[1]) * numbers[size - 1], 1LL * numbers[size - 1] * numbers[size - 2] * numbers[size - 3]);
}

int main() {
    int N;
    scanf("%d", &N);
    assert(N >= 3);
    int *numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);

    int maximum = INT_MIN;

    /* number of multiplications can be reduced using sliding window of size 3. */
    for (int i = 0; i < N - 2; i++)
        maximum = max(maximum, numbers[i] * numbers[i + 1] * numbers[i + 2]);

    printf("maximum = %d\n", maximum);

    int64_t maximum_product = find_maximum_product(numbers, N);
    printf("maximum product = %lld\n", maximum_product);

    free(numbers);
}