#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int N, target;
    scanf("%d%d", &N, &target);
    int *numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);

    bool pair_exists = false;

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (numbers[i] + numbers[j] == target) {
                printf("%d %d\n", numbers[i], numbers[j]);
                pair_exists = true;
            }
            
    if (!pair_exists)
        puts("No such pair");
}
