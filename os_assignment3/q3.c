#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

const int ROWS = (int) 9;
const int COLUMNS = (int) 9;
const int VALUES = (int) 9;
const int OFFSET = (int) 3;
const int SUBGRID_ROWS = (int) ROWS / 3, SUBGRID_COLUMNS = (int) COLUMNS / 3;
const int NUMBER_OF_SUBGRIDS = (ROWS * COLUMNS) / (SUBGRID_ROWS * SUBGRID_COLUMNS);

int **board;

struct co_ordinate {
    int row, column;
};

typedef struct co_ordinate co_ordinate;

void init_co_ordinate(co_ordinate *co_ordinate_, int row, int column) {
    co_ordinate_->column = column, co_ordinate_->row = row;
}

void * check_rows(void *arguments) {
    bool *valid = (bool *) malloc(sizeof(bool));
    *valid = false;
    
    for (int c = 0; c < COLUMNS; c++) {
        bool present[VALUES];

        for (int i = 0; i < VALUES; i++)
            present[i] = false;

        for (int r = 0; r < ROWS; r++)
            present[board[c][r] - 1] = true;
        
        for (int i = 0; i < ROWS; i++)
            if (!present[i])
                pthread_exit((void *) valid);
    }

    *valid = true;
    pthread_exit((void *) valid);
}

void * check_columns(void *arguments) {
    bool *valid = (bool *) malloc(sizeof(bool));
    *valid = false;

    for (int r = 0; r < ROWS; r++) {
        bool present[VALUES];

        for (int i = 0; i < VALUES; i++)
            present[i] = false;

        for (int c = 0; c < COLUMNS; c++)
            present[board[r][c] - 1] = true;
        
        for (int i = 0; i < COLUMNS; i++)
            if (!present[i])
                pthread_exit((void *) valid);
    }

    *valid = true;
    pthread_exit((void *) valid);
}

void * check_subgrid(void *arguments) {
    bool *valid = (bool *) malloc(sizeof(bool));
    co_ordinate *co_ordinate_ = (co_ordinate *) arguments;
    *valid = false;

    bool present[VALUES];

    for (int i = 0; i < VALUES; i++)
        present[i] = false;

    for (int r = co_ordinate_->row; r < co_ordinate_->row + OFFSET; r++)
        for (int c = co_ordinate_->column; c < co_ordinate_->column + OFFSET; c++)
            present[board[r][c] - 1] = true;

    for (int i = 0; i < VALUES; i++)
        if (!present[i])
            pthread_exit((void *) valid);

    *valid = true;
    pthread_exit((void *) valid);
}

bool check_3_X_3_subgrids() {
    co_ordinate *co_ordinates = (co_ordinate *) malloc(NUMBER_OF_SUBGRIDS * sizeof(co_ordinate));
    pthread_t *threads = (pthread_t *) malloc(NUMBER_OF_SUBGRIDS * sizeof(pthread_t));
    bool **valid_subgrids = (bool **) calloc(NUMBER_OF_SUBGRIDS, sizeof(bool *));
    int row = 0, column = 0;

    for (int i = 0; i < NUMBER_OF_SUBGRIDS; i++) {
        init_co_ordinate(co_ordinates + i, row, column);
        pthread_create(threads + i, NULL, check_subgrid, co_ordinates + i);
        column = (column + 3) % COLUMNS;
        row += column == 0 ? 3 : 0;
    }

    for (int i = 0; i < NUMBER_OF_SUBGRIDS; i++)
        pthread_join(threads[i], (void **) &(valid_subgrids[i]));

    free(threads);

    for (int i = 0; i < NUMBER_OF_SUBGRIDS; i++) {
        if (*valid_subgrids[i] == false) {
            free(co_ordinates);
            free(valid_subgrids);
            return false;
        }
    }

    free(co_ordinates);
    free(valid_subgrids);

    return true;
}

int main() {
    board = (int **) malloc(ROWS * sizeof(int *));

    for (int i = 0; i < ROWS; i++)
        board[i] = (int *) malloc(COLUMNS * sizeof(int));

    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLUMNS; c++)
            scanf("%d", &board[r][c]);

    bool *valid_rows, *valid_columns, valid_subgrids;
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, check_rows, NULL);
    pthread_create(&thread2, NULL, check_columns, NULL);

    pthread_join(thread1, (void **) &valid_rows);
    pthread_join(thread2, (void **) &valid_columns);
    valid_subgrids = check_3_X_3_subgrids();

    puts((*valid_rows && *valid_columns && valid_subgrids) ? "Valid Sudoku" : "Invalid Sudoku");

    free(valid_rows);
    free(valid_columns);

    for (int i = 0; i < ROWS; i++)
        free(board[i]);
    
    free(board);
}
