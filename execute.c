#include "shell.h"

/* Function prototypes for built-in commands */
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_ctrld(char **args);

/* Forward declaration of is_builtin_command */
int is_builtin_command(char *command);

/* List of built-in command names and their corresponding functions */
char *builtin_str[] = {"cd", "help", "exit", "^D"};
int (*builtin_func[]) (char **) = {&shell_cd, &shell_help, &shell_exit, &shell_ctrld};

/* Returns the number of built-in commands */
int shell_num_builtins(void)
{
    return (sizeof(builtin_str) / sizeof(char *));
}

/* Placeholder implementations for built-in functions */

int shell_cd(char **args)
{
    /* Placeholder implementation */
    (void)args; /* Prevent unused variable warning */
    return 1;
}

int shell_help(char **args)
{
    /* Placeholder implementation */
    (void)args; /* Prevent unused variable warning */
    return 1;
}

/* Exits the shell */
int shell_exit(char **args)
{
    /* Freeing any allocated memory if necessary */
    (void)args; /* If args are not used in this function */

    /* Exit with status 0 */
    exit(0);
}


int shell_ctrld(char **args)
{
    /* Placeholder implementation */
    (void)args; /* Prevent unused variable warning */
    return 1;
}

/**
 *_fork_fun - foo that create a fork.
 *@arg: Command and values path.
 *@av: Has the name of our program.
 *@env: Environment
 *@lineptr: Command line for the user.
 *@np: ID of proces.
 *@c: Checker add new test
 *Return: 0 success
 */

int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c)
{

	pid_t child;
	int status, i = 0;
	char *format = "%s: %d: %s: not found\n";

	if (arg[0] == NULL)
		return (1);
	for (i = 0; i < shell_num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtin_str[i]) == 0)
			return (builtin_func[i](arg));
	}
	child = fork();
	if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			fprintf(stderr, format, av[0], np, arg[0]);
			if (!c)
				free(arg[0]);
			free(arg);
			free(lineptr);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		return (status);
	}
	return (0);
}

/* Helper function to check if a command is a built-in command */
int is_builtin_command(char *command)
{
    int i;
    for (i = 0; i < shell_num_builtins(); i++)
    {
        if (_strcmp(command, builtin_str[i]) == 0)
            return 1; /* Command is a built-in command */
    }
    return 0; /* Command is not a built-in command */
}

