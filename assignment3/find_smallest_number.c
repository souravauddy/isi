#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdbool.h>
#include "../day11/binary_search_tree.h"

static inline int abs(int x) {
    return x > 0 ? x : -x;
}

int comparator(void * const a, void * const b) {
    return *((int *) a) - *((int *) b);
}

void traverse_and_insert(TREE *tree, int node, int *elements, int *index) {
    if (node == INT_NULL)
        return;

    elements[*index] = *((int *) tree->nodes[node].data);
    *index = *index + 1;

    traverse_and_insert(tree, tree->nodes[node].left, elements, index);
    traverse_and_insert(tree, tree->nodes[node].right, elements, index);
}

int main() {
    int N, sum = 0;
    scanf("%d", &N);
    int *numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
        sum += numbers[i] > 0 ? numbers[i] : 0;
    }

    TREE *binary_search_tree = (TREE *) malloc(sizeof(TREE));
    init_tree(binary_search_tree, sum + 1, sizeof(int), comparator);

    int missing_number = sum + 1;

    for (int i = 0; i < N; i++) {
        int *elements = (int *) malloc((sum + 1) * sizeof(int)), size = 0;
        traverse_and_insert(binary_search_tree, binary_search_tree->root, elements, &size);

        for (int s = 0; s < size; s++) {
            int data = elements[s] + numbers[i];
            insert(binary_search_tree, &data);
        }

        insert(binary_search_tree, numbers[i]);
        free(elements);
    }

    int missing_sum = sum + 1;

    for (int number = 1; number <= sum; number++) {
        if (iterative_search(binary_search_tree, &number) == INT_NULL) {
            missing_sum = number;
            break;
        }
    }

    printf("missing sum = %d\n", missing_sum);
    
    free_tree(binary_search_tree);
    free(numbers);
}

/*
5
1 2 3 4 5

-5 -4 -3 -2 -1 1 2 3 4 5
 0  1  2  3  4 5 6 7 8 9
*/