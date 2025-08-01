#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// returns the index of the next valid player
int find_next_player(int *children, int P, int start) {
    int index = (start + 1) % P; 

    while (children[index] < 0)
        index = (index + 1) % P;

    return index;
}

void eliminate_player(int *player) {
    *player *= -1;
}

void run_case() {
    int P, K, M;
    scanf("%d%d%d", &P, &K, &M);

    int *children = (int *) malloc(P * sizeof(int));

    for (int p = 0; p < P; p++)
        children[p] = p + 1;

    K = (K - 2) % P;

    int current_player = K, other_P = P;

    while (P > 0) {    // till there is a player left
        int rhymes = M;
        
        while (rhymes > 0) {
            current_player = find_next_player(children, other_P, current_player);
            rhymes--;
        }

        assert(children[current_player] > 0);
        printf("%d ", children[current_player]);

        eliminate_player(&children[current_player]);
        P--;
    }

    puts("");
}

int main() {
    int tests;
    scanf("%d", &tests);

    while (tests-- > 0)
        run_case();
}

/*
1
4 1 10
-----------

1 2 3 4

3 
*/