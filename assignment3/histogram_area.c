#include <stdio.h>
#include <stdlib.h>

static inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    int *histogram = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &histogram[i]);

    int previous = histogram[0], count = 1, max_area = 0;

    for (int i = 1; i < N; i++) {
        if (histogram[i] == previous) {
            count++;
            continue;
        }

        max_area = max(max_area, previous * count);
        previous = histogram[i];
        count = 1;
    }

    max_area = max(max_area, previous * count);

    printf("maximum area = %d\n", max_area);
}
