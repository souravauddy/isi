#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(const int argc, const char **argv, const char **envp, const char **apple) {
    // printf("%d\n", argc);

    if (argc <= 2) {
        fprintf(stderr, "Not enough number of arguments present");
        return 0;
    }

    char command[100];
    char arguments[100];
    strcpy(command, argv[1]);
    strcpy(arguments, argv[2]);

    // puts(command);
    // puts(arguments);

    int pid = fork();

    if (pid == 0) {
        char path[100];
        strcpy(path, "/bin/");
        strcat(path, command);
        // puts(command);
        // puts(path);
        execl(path, command, arguments, (char *) NULL);
        return 0;
    }

    wait(NULL);
    puts("This is the parent process waiting for the child process");
}
