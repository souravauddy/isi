#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/shm.h>
#include <sys/wait.h>

const int FORK_ERROR_EXIT_STATUS = (int) -1;
const int CHILD_PROCESS_ERROR_EXIT_STATUS = (int) -2;
const int SHARED_MEMORY_ERROR = (int) 1;
const int DEFAULT_PERMISSION = (int) 0; /* Default permissions are read and write. */

void reverse_subarray(int *array, const int start, const int K) {
    for (int i = 0; i < K / 2; i++) {
        int another = array[start + i];
        array[start + i] = array[start + K - i - 1];
        array[start + K - i - 1] = another;
    }
}

void print_array(const int *array, const int N) {
    for (int i = 0; i < N; i++)
        printf("%d ", array[i]);
    puts("");
}

int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    assert(N % K == 0);

    /* Getting the ID of the shared memory and giving the permissions using the | 0666 of read + write. */
    int shared_memory_id = shmget(IPC_PRIVATE, N * sizeof(int), IPC_CREAT | 0666);

    if (shared_memory_id < 0) {
        fputs("Shared Memory Identifier Error.", stderr);
        return SHARED_MEMORY_ERROR;
    }

    /* Attaching the Shared Memory.*/
    int *array = (int *) shmat(shared_memory_id, NULL, DEFAULT_PERMISSION);

    for (int i = 0; i < N; i++)
        scanf("%d", &array[i]);

    for (int i = 0; i < N / K; i++) {
        pid_t process_id = fork();

        if (process_id < 0) {
            fputs("Fork had an error.", stderr);
            return FORK_ERROR_EXIT_STATUS;
        }

        /* In the child process. */
        if (process_id == 0) {
            reverse_subarray(array, i * K, K);
            
            /* Detach the shared memory. */
            shmdt(array);
            return 0;
        }
    }

    for (int i = 0; i < N; i++)
        wait(NULL);

    print_array(array, N);

    /* Detach the Shared Memory. */
    shmdt(array);

    /* Destroy the Shared Memory. */
    shmctl(shared_memory_id, IPC_RMID, NULL);
}