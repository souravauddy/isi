    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>

const char MIN_DIGIT = (char) '0';
const int FORK_ERROR_EXIT_STATUS = (int) -1;
const int CHILD_PROCESS_ERROR_EXIT_STATUS = (int) -2;
const int SHARED_MEMORY_ERROR = (int) 1;
const int DEFAULT_PERMISSION = (int) 0; /* Default permissions are read and write. */

uint32_t perform_task(const char *row) {
    uint32_t sum = 0;
    
    for (int i = 0; row[i]; i++)
        sum += (row[i] - MIN_DIGIT);
    
    return sum;
}

uint32_t argmax(const uint32_t *array, const int N) {
    int max_index = 0;

    for (int i = 1; i < N; i++)
        if (array[i] > array[max_index])
            max_index = i;

    return max_index;
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    char **matrix = (char **) malloc(N * sizeof(char *));

    for (int i = 0; i < N; i++) {
        matrix[i] = (char *) malloc((M + 1) * sizeof(char));
        scanf("%s", matrix[i]);
    }

    /* Getting the ID of the shared memory and giving the permissions using the | 0666 of read + write. */
    int shared_memory_id = shmget(IPC_PRIVATE, N * sizeof(uint32_t), IPC_CREAT | 0666);

    if (shared_memory_id < 0) {
        fputs("Shared Memory Identifier Error.", stderr);
        return SHARED_MEMORY_ERROR;
    }

    /* Attaching the Shared Memory.*/
    uint32_t *count_ones = (uint32_t *) shmat(shared_memory_id, NULL, DEFAULT_PERMISSION);

    for (int i = 0; i < N; i++) {
        pid_t process_id = fork();

        if (process_id < 0) {
            fputs("Fork had an issue.", stderr);
            return FORK_ERROR_EXIT_STATUS;
        }

        /* In the child process. */
        if (process_id == 0) {
            count_ones[i] = perform_task(matrix[i]);

            /* Detach the shared memory in the child process. */
            shmdt(count_ones);
            return 0; /* Child process exited successfully. */
        }
    }

    for (int i = 0; i < N; i++)
        wait(NULL);

    /* All the child processes exit.    */
    printf("The row with the maximum number of ones is = %u.\n", 1 + argmax(count_ones, N));

    /* Detach the Shared Memory. */
    shmdt(count_ones);

    /* Destroy Shared Memory. */
    shmctl(shared_memory_id, IPC_RMID, NULL);

    for (int i = 0; i < N; i++)
        free(matrix[i]);

    free(matrix);
}
