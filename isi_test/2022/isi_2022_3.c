#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ** allocate_matrix(int **matrix, int row, int column) {
    matrix = (int **) malloc(row * sizeof(int *));

    for (int r = 0; r < row; r++)
        matrix[r] = (int *) malloc(column * sizeof(int));

    return matrix;
}

void input(int **matrix, int row, int column) {
    for (int r = 0; r < row; r++)
        for (int c = 0; c < column; c++)
            scanf("%d", &matrix[r][c]);
}

void print_matrix(int **matrix, int row, int column) {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++)
            printf("%d ", matrix[r][c]);
        
        puts("");
    }
}

int ** input_matrix(int **matrix, int *row, int *column) {
    scanf("%d%d", row, column);
    matrix = allocate_matrix(matrix, *row, *column);
    input(matrix, *row, *column);
    return matrix;
}

void matrix_multiply(int **A, int AN, int AM, int **B, int BN, int BM, int **result, int RN, int RM) {
    for (int r = 0; r < RN; r++) {
        for (int c = 0; c < RM; c++) {
            result[r][c] = 0;

            for (int k = 0; k < BN; k++)
                result[r][c] += A[r][k] * B[k][c];
        }
    }
}

int main() {
    int AN, AM, BN, BM, CN, CM;
    int **A, **B, **C;
    
    A = input_matrix(A, &AN, &AM);
    B = input_matrix(B, &BN, &BM);
    C = input_matrix(C, &CN, &CM);

    if (AM != BN || BM != CN) {
        puts("ERROR");
        return 0;
    }

    int **intermediate, IN = AN, IM = BM;
    intermediate = allocate_matrix(intermediate, IN, IM);

    matrix_multiply(A, AN, AM, B, BN, BM, intermediate, IN, IM);

    int **result, RN = AN, RM = CM;
    result = allocate_matrix(result, RN, RM);

    matrix_multiply(intermediate, IN, IM, C, CN, CM, result, RN, RM);

    print_matrix(result, RN, RM);
}
