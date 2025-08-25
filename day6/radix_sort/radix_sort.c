#include <stdio.h>
#include <math.h>
#include "../common.h"

#define debug(x) printf("%s = %d\n", #x, x)

const int RADIX = (int) 2;

static inline int number_of_digits(int number, const int RADIX) {
    int digits = 0;

    while (number > 0) {
        digits++;
        number /= RADIX;
    }

    return digits;
}

static inline int max(int a, int b) {
    return a > b ? a : b;
}

static inline void print_array(int *numbers, int N) {
    for (int i = 0; i < N; i++)
        printf("%d ", numbers[i]);
    puts("");
}

void radix_sort(int *numbers, int N) {
    int **buckets = (int **) malloc(RADIX * sizeof(int *));
    int *count = (int *) malloc(RADIX * sizeof(int));

    for (int r = 0; r < RADIX; r++)
        buckets[r] = (int *) malloc(N * sizeof(int));

    // matrix_alloc(numbers, RADIX, N, int);
    int max_number_length = 0, divisor = 1;

    for (int i = 0; i < N; i++)
        max_number_length = max(max_number_length, number_of_digits(numbers[i], RADIX));

    while (max_number_length-- > 0) {
        memset(count, 0, RADIX * sizeof(int));

        for (int i = 0; i < N; i++) {
            int radix_index = (numbers[i] / divisor) % RADIX;;
            buckets[radix_index][count[radix_index]++] = numbers[i];
        }

        for (int r = 0, index = 0; r < RADIX; r++)
            for (int c = 0; c < count[r]; c++)
                numbers[index++] = buckets[r][c];
        
        divisor *= RADIX;
    }

    for (int r = 0; r < RADIX; r++)
        free(buckets[r]);

    free(buckets);
}

int main() {
    int N;
    scanf("%d", &N);
    int *numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);

    print_array(numbers, N);
    radix_sort(numbers, N);    
    print_array(numbers, N);

    free(numbers);
}
