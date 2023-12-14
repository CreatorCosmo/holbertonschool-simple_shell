#include "shell.h"
/**
 * main - Main arguments functions
 * @ac: Count of argumnents
 * @av: Arguments
 * @env: Environment
 * Return: _exit = 0.
 */

int main(int ac, char **av, char **env)
{
    int pathValue = 0, status = 0, is_path = 0;
    char *line = NULL, **commands = NULL;
    (void)ac; /* Suppress unused parameter warning */
    
    while (1) /* Infinite loop for the shell */
    {
        errno = 0;
        line = _getline_command(); /* Reads user input */
        if (line == NULL && errno == 0)
            return (0); /* Exit if no input is received */

        if (line)
        {
            pathValue++;
            commands = tokenize(line); /* Tokenizes or parses user input */
            if (!commands || !commands[0]) /* Check if commands or commands[0] is null */
            {
                free(line);
                continue; /* Skip the current iteration if null */
            }
            if (!_strcmp(commands[0], "env")) /* Checks if user wrote 'env' */
                _getenv(env);
            else
            {
                is_path = _values_path(&commands[0], env); /* Checks if command is in PATH */
                status = _fork_fun(commands, av, env, line, pathValue, is_path);
                if (status == 200)
                {
                    free(line);
                    return (0); /* Exit if status is 200 */
                }
            }
            free(commands); /* Free command array */
        }
        free(line); /* Free input line */
    }
    return (status); /* Return the last command's status */
}
