#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void forward_backward_sort(int *numbers, const int N) {
    for (int iter = 0; iter < N; iter++) {
        bool swapped = false;

        for (int i = iter; i < N - iter - 1; i++) {
            if (numbers[i] > numbers[i + 1]) {
                swap(&numbers[i], &numbers[i + 1]);
                swapped = true;
            }
        }

        for (int i = N - iter - 1; i > iter; i--) {
            if (numbers[i - 1] > numbers[i]) {
                swap(&numbers[i], &numbers[i - 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

int main() {
    int _capacity = 1, number_of_elements = 0;
    int *numbers = (int *) malloc(_capacity * sizeof(int));
    assert(numbers);

    while (scanf("%d", &numbers[number_of_elements]) != EOF) {
        number_of_elements++;

        if (number_of_elements == _capacity) {
            _capacity *= 2;
            numbers = (int *) realloc(numbers, _capacity * sizeof(int));
            assert(numbers);
        }
    }

    printf("number of elements = %d\n", number_of_elements);

    forward_backward_sort(numbers, number_of_elements);

    for (int i = 0; i < number_of_elements; i++)
        printf("%d ", numbers[i]);
    puts("");

    free(numbers);
}
