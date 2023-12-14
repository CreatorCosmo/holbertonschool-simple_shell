#include "shell.h"

/**
 * main - Entry point for the shell
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 * Return: Exit status
 */
int main(int ac, char **av, char **env)
{
    char *line = NULL;
    char **commands = NULL;
    int status = 0, is_path = 0, pathValue = 0;

    (void)ac; /* Unused parameter */

    while (1) {
        errno = 0;
        line = _getline_command(); /* Read user input */
        if (line == NULL) {
            if (errno == 0) {
                return 0; /* EOF reached */
            }
            perror("Readline error");
            continue;
        }

        commands = tokenize(line); /* Tokenize user input */
        if (commands == NULL || commands[0] == NULL) {
            free(line);
            continue; /* Handle empty commands */
        }

        if (_strcmp(commands[0], "env") == 0) {
            _getenv(env);
        } else {
            is_path = _values_path(&commands[0], env); /* Handle PATH */
            pathValue++;
            status = _fork_fun(commands, av, env, line, pathValue, is_path);
            if (status == 200) {
                free(line);
                break; /* Exit command invoked */
            }
        }

        if (is_path == 0) {
            free(commands[0]); /* Freeing if path was modified */
        }
        free(commands); /* Free tokenized commands */
        free(line); /* Free input line */
    }

    return status;
}

