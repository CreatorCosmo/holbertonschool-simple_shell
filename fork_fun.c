#include "shell.h"

/**
 * _fork_fun - Forks a process to execute a command
 * @arg: Arguments for the command
 * @av: Argument vector (unused in this example)
 * @env: Environment variables
 * @lineptr: Line pointer (unused in this example)
 * @np: Some integer parameter (unused in this example)
 * @c: Some integer parameter (unused in this example)
 * Return: Status code (0 for success, non-zero for error)
 */
int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c)
{
    pid_t pid;
    int status;

    /* Unused parameters */
    (void)av;  
    (void)lineptr;
    (void)np;
    (void)c;

    pid = fork();
    if (pid == -1) {
        /* Fork failed */
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /* In child process */
        if (execve(arg[0], arg, env) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        /* In parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return WEXITSTATUS(status);
}

