#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int N = (int) 9;
const int HASH_SIZE = (int) 10;

bool valid(const int *count) {
    for (int i = 1; i < HASH_SIZE; i++)
        if (count[i] != 1)
            return false;
    
    return true;
}

int main() {
    int **game = (int **) malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++)
        game[i] = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &game[i][j]);

    for (int i = 0; i < N; i++) {
        int count1[10] = {0}, count2[10] = {0};
        
        for (int j = 0; j < N; j++) {
            count1[game[i][j]]++;
            count2[game[j][i]]++;
        }

        if (!valid(count1) || !valid(count2)) {
            puts("Invalid");
            return 0;
        }
    }
       
    for (int i = 0; i < N; i += 3) {
        for (int j = 0; j < N; j += 3) {
            int count[10] = {0};    

            for (int r = i; r < i + 3; r++)
                for (int c = j; c < j + 3; c++)
                    count[game[r][c]]++;
            
            if (!valid(count)) {
                puts("Invalid");
                return 0;
            }
        }
    }

    puts("Valid");
}
