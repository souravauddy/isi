#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool property_1(int *numbers, int size) {
    for (int i = 0; i < size - 1; i++)
        if (numbers[i] < numbers[i + 1])
            return false;

    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        int another = b;
        b = a % b;
        a = another;
    }

    return a;
}

bool property_2(int *numbers, int size) {
    int p_sum = numbers[size - 1], q_sum = 0;

    for (int i = 0; i < size - 1; i++) {
        p_sum += numbers[i];
        q_sum += numbers[i] - numbers[i + 1];
    }

    return gcd(p_sum, q_sum) == 1;    
}

int main() {
    int N;
    scanf("%d", &N);
    int *numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);

    printf(property_1(numbers, N) && property_2(numbers, N) ? "" : "Not ");
    puts("A Sequence");
}
