#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    bool *present = (bool *) malloc((N + 1) * sizeof(bool));
    memset(present, false, (N + 1) * sizeof(bool));

    for (int i = 0; i < N; i++) {
        int number;
        scanf("%d", &number);

        if (number > 0 && number <= N)
            present[number] = true;            
    }

    int missing_number = N + 1;

    for (int number = 1; number < N + 1; number++)
        if (!present[number]) {
            missing_number = number;
            break;
        }

    printf("missing number = %d\n", missing_number);
    free(present);
}