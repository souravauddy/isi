#include <stdio.h>
#include <stdlib.h>

int main() {
    int M, N;
    scanf("%d%d", &M, &N);

    double *taps = (double *) malloc(M * sizeof(double));
    double *drains = (double *) malloc(N * sizeof(double));

    for (int t = 0; t < M; t++)
        scanf("%lf", &taps[t]);

    for (int d = 0; d < N; d++)
        scanf("%lf", &drains[d]);

    double taps_power = 0, drains_power = 0;

    for (int t = 0; t < M; t++)
        taps_power += 1 / taps[t];

    for (int d = 0; d < N; d++)
        drains_power += 1 / drains[d];

    if (taps_power < drains_power)
        puts("(A)");
    else
        printf("(B) %0.2lf\n", 1 / (taps_power - drains_power));

    if (taps_power > drains_power)
        puts("(C)");
    else
        printf("(D) %0.2lf\n", 1 / (drains_power - taps_power));
}
