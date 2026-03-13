#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <time.h>

const char MIN_DIGIT = (char) '0';
const int FORK_ERROR_EXIT_STATUS = (int) -1;
const int CHILD_PROCESS_ERROR_EXIT_STATUS = (int) -2;

uint32_t perform_task(const char *row) {
    uint32_t sum = 0;
    
    for (int i = 0; row[i]; i++)
        sum += (row[i] - MIN_DIGIT);
    
    return sum;
}

uint32_t argmax(const int *array, const int N) {
    int max_index = 0;

    for (int i = 0; i < N; i++)
        printf("%d ", array[i]);
    puts("");

    for (int i = 1; i < N; i++)
        if (array[i] > array[max_index])
            max_index = i;

    return max_index;
}

static inline void free_common_memory(char **matrix, pid_t *process_ids, const int N) {
    for (int i = 0; i < N; i++)
        free(matrix[i]);

    free(matrix);
    free(process_ids);
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    char **matrix = (char **) malloc(N * sizeof(char *));

    for (int i = 0; i < N; i++) {
        matrix[i] = (char *) malloc((M + 1) * sizeof(char));
        scanf("%s", matrix[i]);
    }

    pid_t *process_ids = (pid_t *) malloc(N * sizeof(pid_t));

    for (int i = 0; i < N; i++) {
        process_ids[i] = fork();

        if (process_ids[i] < 0) {
            fputs("Fork had an issue.", stderr);
            return FORK_ERROR_EXIT_STATUS;
        }
        
        /* Inside the child process. */
        if (process_ids[i] == 0) {
            // free_common_memory(matrix, process_ids, N); This is wrong because of COPY_ON_WRITE optimization.
            return perform_task(matrix[i]);
        }
    }

    int *exit_status = (int *) malloc(N * sizeof(int));
    int *row_ones_count = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        waitpid(process_ids[i], &exit_status[i], 0);

        /* The child process has exited normally. */
        if (exit_status[i] < 0) {
            fprintf(stderr, "Child process %d with pid %d did not finish sucessfully.\n", i, process_ids[i]);
            return CHILD_PROCESS_ERROR_EXIT_STATUS;
        }
            
        row_ones_count[i] = WEXITSTATUS(exit_status[i]);
    }

    /* All the child processes exit*/
    printf("The row with the maximum number of ones is = %d\n", 1 + argmax(row_ones_count, N)); 

    free_common_memory(matrix, process_ids, N);
    free(exit_status);
    free(row_ones_count);
}