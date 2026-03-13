#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int FORK_ERROR = (int) -1;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        puts("There was some error with the fork command.");
        return FORK_ERROR;
    }

    if (pid == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        return 0;
    }

    printf("This is the parent process the child's pid is = %d\n", pid);
}

