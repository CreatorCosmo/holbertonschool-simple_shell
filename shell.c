#include "shell.h"

/**
 * main - Main arguments functions
 * @ac: Count of arguments
 * @av: Arguments
 * @env: Environment
 * Return: Exit status
 */
int main(int ac, char **av, char **env)
{
	int pathValue = 0, status = 0, is_path = 0, final_status = 0;
	char *line = NULL, **commands = NULL;
	(void)ac;

	while (1)
	{
		errno = 0;
		line = _getline_command();
		if (line == NULL && errno == 0)
			return (final_status); /* Return the final exit status */

		if (line)
		{
			pathValue++;
			commands = tokenize(line);
			if (!commands)
			{
				free(line);
				continue;
			}
			if (commands[0] == NULL)
			{
				free(commands);
				free(line);
				continue;
			}

			if (!_strcmp(commands[0], "env"))
				_getenv(env);
			else
			{
				is_path = _values_path(&commands[0], env);
				status = _fork_fun(commands, av, env, line, pathValue, is_path);
				if (status != 0)
					final_status = status; /* Update final_status with the command's exit status */

				if (status == 200)
				{
					free(line);
					return (final_status); /* Return the final exit status */
				}
				if (is_path == 0)
					free(commands[0]);
			}
			free(commands);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(final_status); /* Exit with final_status */
		}
		free(line);
	}
	return (final_status); /* Return the final exit status */
}

