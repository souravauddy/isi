#define _POSIX_C_SOURCE 200809L

#include "/Users/souravauddy/Documents/isi/day14/avl_tree.h"
#include "parser.h"

#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <pwd.h>
    
#define MAX_FOREGROUND_PROCESSES (int) 100

const int WHANG = (int) 0;
const int MAX_COMMANDS = (int) 20;
const int BUFFER_SIZE = (int) 2 << 10;
const int HOST_BUFFER_SIZE = (int) 256;
const int MAX_ARGUMENT_SIZE = (int) 1 << 8;
char *HOME_DIRECTORY;
const int MAX_BACKGROUND_PROCESSES = (int) 100;

extern const int MAX_ARGUMENTS;
extern const char *SERIAL_OPERATOR, *PARALLEL_OPERATOR, *BACKGROUND_OPERATOR, *EITHER_OPERATOR;

char *HOSTNAME;
avl_tree *background_processes;
pid_t foreground_running_process_ids[MAX_FOREGROUND_PROCESSES];
size_t number_of_foreground_running_processes;

enum command_type {
    FOREGROUND_COMMAND, BACKGROUND_COMMAND,
};

struct command {
    char *command_name, **arguments;
    int type, number_of_arguments;
};

typedef struct command command;

void init_command(command *command_, char *command_name, char **arguments, int number_of_arguments, int type) {
    command_->type = type;
    command_->arguments = arguments;
    command_->command_name = command_name;
    command_->number_of_arguments = number_of_arguments;
}

void print_command(command *command_) {
    printf("command name: %s\n", command_->command_name);

    for (int i = 0; i < command_->number_of_arguments; i++)
        printf("argument no %d: %s\n", i + 1, command_->arguments[i]);

    printf("command type: %s\n", command_->type == FOREGROUND_COMMAND ? "FOREGROUND" : "BACKGROUND");
    printf("number of arguments = %d\n", command_->number_of_arguments);
}

static inline void process_hostname(char *hostname) {
    int N = strlen(hostname);
    hostname[N - 6] = '\0';
}

void _terminate(avl_tree *processes, const int node) {
    if (node == INT_NULL)
        return;
    
    _terminate(processes, processes->nodes[node].left);
    _terminate(processes, processes->nodes[node].right);
    kill(*((pid_t *) processes->nodes[node].data), SIGKILL);
    delete(processes, processes->nodes[node].data);
}

void terminate(avl_tree *background_processes) {
    _terminate(background_processes, background_processes->root);
}

void print_shell_prompt(const char *hostname) {
    uid_t userid = getuid();
    struct passwd *user_infomation = getpwuid(userid);
    char *current_directory = getcwd(NULL, 0);

    printf("%s@%s:%s$ ", user_infomation->pw_name, hostname, current_directory);
    fflush(stdout);
    free(current_directory);
}

int execute_foreground_command(command *command_, parser *argument_parser, avl_tree *background_processes) {
    if (strcmp(command_->command_name, "exit") == 0) {
        terminate(background_processes);
        exit(0);
    }

    if (strcmp(command_->command_name, "cd") == 0) {
        char *path = command_->arguments[1];
        path = path == NULL || strcmp(path, "~") == 0 ? (char *) HOME_DIRECTORY : path;
        
        if (chdir(path) == -1)
            perror("cd");

        return 0;
    }

    foreground_running_process_ids[0] = fork();
    number_of_foreground_running_processes = 1;
    int status = 0;

    if (foreground_running_process_ids[0] == 0) {
        setpgid(0, 0);
        execvp(command_->command_name, command_->arguments);
        _exit(1);
    }   

    setpgid(foreground_running_process_ids[0], foreground_running_process_ids[0]);
    waitpid(foreground_running_process_ids[0], &status, WHANG);
    number_of_foreground_running_processes = 0;
    
    return WEXITSTATUS(status);
}

int execute_background_command(command *command_, parser *argument_parser, avl_tree *background_processes) {
    pid_t *pid = (pid_t *) malloc(sizeof(pid_t));
    *pid = fork();

    if (*pid == 0) {
        /* This is the child process. */
        setpgid(0, 0);
        execvp(command_->command_name, command_->arguments);
        _exit(1);
    }

    setpgid(*pid, *pid);
    /* This is the parent process. */
    insert(background_processes, pid);

    return 0;
}

int serial_command_executor(command *commands, int number_of_commands, avl_tree *background_processes, parser *argument_parser) {
    /*
        * There a two types of commands in the serial chain, foreground and background process.
        * If the process is a foreground process the shell waits for it.
        * The background processes pid are kept in a avl_tree for efficient insertion and deletion when a process is deleted.
        * If the process is a background process the shell does not wait for it, and uses the sighandler asynchronously.
    */

    for (int i = 0; i < number_of_commands; i++) {
        if (commands[i].type == FOREGROUND_COMMAND) {
            int status = execute_foreground_command(commands + i, argument_parser, background_processes);
            
            if ((!WIFEXITED(status) || WEXITSTATUS(status) != 0)) {
                fprintf(stderr, "%s did not execute successfully with exit code %d.\n", commands[i].command_name, WEXITSTATUS(status));
                return WEXITSTATUS(status);
            }
        } else {
            execute_background_command(commands + i, argument_parser, background_processes);
        }
    }

    /* All the foreground commands were sucessful. */
    return 0;
}

int parallel_command_executor(command *commands, int number_of_commands, avl_tree *background_processes, parser *argument_parser) {
    assert(number_of_foreground_running_processes == 0);

    // sigset_t mask, oldmask;

    // /* Block SIGCHLD while creating children */
    // sigemptyset(&mask);
    // sigaddset(&mask, SIGCHLD);
    // sigprocmask(SIG_BLOCK, &mask, &oldmask);

    for (int i = 0; i < number_of_commands; i++) {
        if (commands[i].type == FOREGROUND_COMMAND) {
            foreground_running_process_ids[number_of_foreground_running_processes++] = fork();

            if (foreground_running_process_ids[number_of_foreground_running_processes - 1] == 0) {
                setpgid(0, 0);
                execvp(commands[i].command_name, commands[i].arguments);
                _exit(1);
            }

            setpgid(foreground_running_process_ids[number_of_foreground_running_processes - 1], foreground_running_process_ids[number_of_foreground_running_processes - 1]);
        } else {
            pid_t *pid = (pid_t *) malloc(sizeof(pid_t));
            *pid = fork();
            
            if (*pid == 0) {
                setpgid(0, 0);
                execvp(commands[i].command_name, commands[i].arguments);
                _exit(1);
            }

            setpgid(*pid, *pid);
            insert(background_processes, pid);
        }
    }

    // sigprocmask(SIG_SETMASK, &oldmask, NULL);

    int *statuses = (int *) malloc(number_of_foreground_running_processes * sizeof(int));

    for (int i = 0; i < number_of_foreground_running_processes; i++)
        waitpid(foreground_running_process_ids[i], &statuses[i], 0);

    // puts("comes here");
    number_of_foreground_running_processes = 0;

    free(statuses);

    return 0;
}

bool invalid_command(char *token) {
    return strcmp(token, SERIAL_OPERATOR) == 0 || strcmp(token, PARALLEL_OPERATOR) == 0;
}

int execute_command(parser *argument_parser, avl_tree *background_processes) {
    /* 
        * This assumes that either serial or parallel types of commands will be there in a chain but not both.
        * The inidividual command can be foreground or background command.
        * There cannot be any command after a background command (This is the default linux shell behaviour).
    */

    command *commands = (command *) malloc(MAX_COMMANDS * sizeof(command));
    int number_of_commands, command_start = 0;
    bool serial_command = true;

    if (invalid_command(argument_parser->tokens[argument_parser->number_of_tokens - 1])) {
        fprintf(stderr, "Parsing error\n");
        return 1;
    }

    for (number_of_commands = 0; command_start < argument_parser->number_of_tokens; number_of_commands++) {
        int command_end = command_start;
        char **arguments = (char **) malloc(MAX_ARGUMENTS * sizeof(char *));

        while (command_end < argument_parser->number_of_tokens && strcmp(argument_parser->tokens[command_end], "&&") && strcmp(argument_parser->tokens[command_end], "&") && strcmp(argument_parser->tokens[command_end], "&&&")) {
            arguments[command_end - command_start] = argument_parser->tokens[command_end];
            command_end++;
        }

        if (serial_command && command_end < argument_parser->number_of_tokens && strcmp(argument_parser->tokens[command_end], "&&&") == 0)
            serial_command = false;

        int command_execution_type = command_end < argument_parser->number_of_tokens && strcmp(argument_parser->tokens[command_end], "&") == 0 ? BACKGROUND_COMMAND : FOREGROUND_COMMAND;
        arguments[command_end - command_start] = NULL;

        if (command_execution_type == BACKGROUND_COMMAND && command_end + 1 < argument_parser->number_of_tokens) {
            fprintf(stderr, "Parsing error\n");
            return 1;
        }

        init_command(
            commands + number_of_commands,
            argument_parser->tokens[command_start],
            arguments,
            command_end - command_start + 1,
            command_execution_type
        );
        
        command_start = command_end + 1;
    }

    // for (int i = 0; i < number_of_commands; i++)
    //     print_command(commands + i);

    if (serial_command) {
        serial_command_executor(commands, number_of_commands, background_processes, argument_parser);
    } else {
        // puts("It should not come here for now.");
        // assert(false);
        parallel_command_executor(commands, number_of_commands, background_processes, argument_parser);
    }

    free(commands);

    return 0;
}

int pid_comparator(void *pid1, void *pid2) {
    return *((pid_t *) pid1) - *((pid_t *) pid2);
}

bool foreground_process(pid_t pid) {
    for (int i = 0; i < number_of_foreground_running_processes; i++)
        if (foreground_running_process_ids[i] == pid)
            return true;

    return false;
}

void _background_process_handler(int singal) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (foreground_process(pid))
            continue;

        int index = search(background_processes, &pid);

        if (index == INT_NULL)
            continue;

        if (WIFEXITED(status)) {
            delete(background_processes, &pid);
            // fprintf(stdin, "\n");
            printf("\nprocess %d finished with exit code %d.\n", pid, WEXITSTATUS(status));
            print_shell_prompt(HOSTNAME);
        }
    }
}

void _interrupt_handler(int signal) {
    // for (int i = 0; i < number_of_foreground_running_processes; i++)
    //     fprintf(stderr, "command stopped\n");

    if (number_of_foreground_running_processes == 0) {
        // puts("comes here");
        puts("");
        print_shell_prompt(HOSTNAME);
        return;
    }

    for (int i = 0; i < number_of_foreground_running_processes; i++) {
        if (kill(foreground_running_process_ids[i], SIGINT) == 0) {
            fputs("\ncommand stopped.\n", stderr);
        } else {
            if (errno == ESRCH) {
                fprintf(stderr, "Process %d could not be found\n", foreground_running_process_ids[i]);
                continue;
            }

            fprintf(stderr, "could not terminate the foreground process.");
            exit(1);
        }
    }

    number_of_foreground_running_processes = 0;
    // print_shell_prompt(HOME_DIRECTORY);
    // puts("");
}

int main(const int argc, const char **argv, const char **envp, const char **apple) {
    HOME_DIRECTORY = getenv("HOME");
    background_processes = (avl_tree *) malloc(sizeof(avl_tree));
    init_tree(background_processes, MAX_BACKGROUND_PROCESSES, sizeof(pid_t), pid_comparator, free);

    /*
        * When the child terminates it sends "SIGCHLD" to the parent and this handles the singal and removes it from the background processes list.
        * This is done using asynchronous programming.
    */

    struct sigaction background_process_handler;
    background_process_handler.sa_handler = _background_process_handler;
    sigemptyset(&background_process_handler.sa_mask);
    background_process_handler.sa_flags = SA_RESTART;

    struct sigaction keyboard_interrupt_handler;
    keyboard_interrupt_handler.sa_handler = _interrupt_handler;
    sigemptyset(&keyboard_interrupt_handler.sa_mask);
    keyboard_interrupt_handler.sa_flags = SA_RESTART;

    sigaction(SIGINT, &keyboard_interrupt_handler, NULL);
    sigaction(SIGCHLD, &background_process_handler, NULL);

    char hostname[HOST_BUFFER_SIZE];
    gethostname(hostname, HOST_BUFFER_SIZE);
    process_hostname(hostname);
    HOSTNAME = hostname;

    while (true) {
        print_shell_prompt(hostname);

        char command[BUFFER_SIZE];
        
        if (fgets(command, BUFFER_SIZE, stdin) == NULL) {
            fputs("fgets failed.", stderr);
            exit(1);
        }

        parser argument_parser;
        init_parser(&argument_parser);
        parse(&argument_parser, command);

        execute_command(&argument_parser, background_processes);
    }

    free_tree(background_processes);
}
