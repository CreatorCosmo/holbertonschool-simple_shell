#include "shell.h"

/**
 * _fork_fun - Creates a child process to execute a command
 * @arg: Command and arguments to execute
 * @av: Argument vector (unused)
 * @env: Environment variables
 * @lineptr: Line pointer (unused)
 * @np: Integer parameter (unused)
 * @c: Integer parameter (unused)
 * Return: Status of the executed command
 */
int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c) {
    pid_t pid;
    int status;

    /* Suppress unused parameter warnings */
    (void)av;
    (void)lineptr;
    (void)np;
    (void)c;

    pid = fork();
    if (pid == -1) {
        /* Fork failed */
        perror("fork");
        return -1;
    } else if (pid == 0) {
        /* In child process */
        execve(arg[0], arg, env);
        /* execve only returns on error */
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        /* In parent process, waiting for child to finish */
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return -1;
        }

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            /* Child process didn't exit normally */
            return -1;
        }
    }
}

