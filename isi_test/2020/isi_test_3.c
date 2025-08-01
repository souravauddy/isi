#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int copy = *a;
    *a = *b;
    *b = copy;
}

void sort(int *numbers, int N) {
    for (int i = 0; i < N; i++) {
        bool swapped = false;

        for (int j = i + 1; j < N; j++)
            if (numbers[i] > numbers[j])
                swap(&numbers[i], &numbers[j]), swapped = true;

        if (!swapped)
            break;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    int *numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);

    sort(numbers, N);

    int h_index = 0;

    for (int i = 0; i < N; i++) {
        if (N - i > h_index && numbers[i] >= N - i) {
            h_index = N - i;
        }
    }

    printf("%d\n", h_index);
}
