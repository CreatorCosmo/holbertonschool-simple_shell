#include "shell.h"

/* Function prototypes for built-in commands */
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_ctrld(char **args);
int shell_ls(char **args); /* Prototype for shell_ls */

/* List of built-in command names and their corresponding functions */
char *builtin_str[] = {"cd", "help", "exit", "^D", "ls"};
int (*builtin_func[]) (char **) = {&shell_cd, &shell_help, &shell_exit, &shell_ctrld, &shell_ls};

/* Returns the number of built-in commands */
int shell_num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}

/* Built-in function implementations */

/* Changes the current directory */
int shell_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "hsh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("hsh");
		}
	}
	return (1);
}

/* Prints help information for the shell */
int shell_help(char **args)
{
	int i;
	printf("Oscar Bedat and Andres Henderson\n");
	printf("If you need help, call 1-800-help\n");
	(void)args; /* Args are not used in this function */
	for (i = 0; i < shell_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	return (1);
}

/* Exits the shell */
int shell_exit(char **args)
{
	(void)args; /* Args are not used in this function */
	free(args);
	return (200);
}

/* Handles "^D" input (end-of-transmission) */
int shell_ctrld(char **args)
{
	(void)args; /* Args are not used in this function */
	free(args);
	return (200);
}

/* Placeholder for the 'ls' command */
int shell_ls(char **args)
{
	printf("'ls' is not a built-in command in this shell.\n");
	(void)args; /* Args are not used in this function */
	return (1);
}

/* Creates a child process to execute a command */
int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c)
{
	pid_t child;
	int status, i = 0;
	char *format = "%s: %d: %s: not found\n";

	if (arg[0] == NULL)
		return (1); /* If no command is provided, return 1 */

	/* Check if the command is a built-in function */
	for (i = 0; i < shell_num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtin_str[i]) == 0)
			return (builtin_func[i](arg)); /* Execute the built-in function */
	}

	child = fork();
	if (child == 0) /* Child process */
	{
		if (execve(arg[0], arg, env) == -1) /* Execute the command */
		{
			fprintf(stderr, format, av[0], np, arg[0]); /* Print error if execve fails */
			if (!c)
				free(arg[0]);
			free(arg);
			free(lineptr);
			exit(errno); /* Exit with error code */
		}
	}
	else
	{
		wait(&status); /* Parent process waits for the child to finish */
		if (WIFEXITED(status))
			return WEXITSTATUS(status); /* Return the exit status of the child process */
	}
	return (0); /* Return 0 on success */
}

