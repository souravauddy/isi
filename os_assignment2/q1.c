#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Some error is there with fork");
        return 0;
    }

    if (pid == 0) {
        puts("I am the child.");
        return 0;
    } else {
        wait(NULL);
        printf("This is the parent, and child's pid = %d\n", pid);
    }

    return 0;
}
