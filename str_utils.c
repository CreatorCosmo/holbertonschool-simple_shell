#include "shell.h"

/**
 * _strcat - ncatenates two strings
 *
 * @dest: Destination string
 *
 * @src: Origin string
 * Return: Always 0
 */



char *_strcat(char *dest, char *src)
{
	int i, j = 0;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;

	}
	dest[i] = '\0';
return (dest);
}



/**
 * _strcmp - Compares two strings
 *
 * @s1: a string
 * @s2: Another string
 *
 * Return: multiple returns
 *
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int val;

	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
		i++;
val = s1[i] - s2[i];
return (val);

}

/**
 * _strlen - gets the size of a string
 * @s: the string to measure
 * Return: the length of the string
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
		;

	return (i);
}

/**
 *_strncmp -  function that compares two strings.
 *@s1: string one
 *@s2: string two
 *@n: number of characters
 * Return: diference
 */

size_t _strncmp(char *s1, char *s2, size_t n)
{
	size_t i, j;

	for (j = 0; s1[j] != '\0' && j < n; j++)
	{
		i = s1[j] - s2[j];

		if (i != 0)
		{
			return (i);
		}
	}
	return (0);
}

/**
 * _strcpy - copies the string pointed to by src into dest
 * @dest: destination of the copy
 * @src: source of the copy
 *
 * Return: char pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i + 1] = 0;
	return (dest);
}





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














#include "shell.h"
/**
 * tokenize - tokenizes a stirng
 * @lineptr: what the user inputed
 * Return: a ptr to arr of ptrs
 */

char **tokenize(char *lineptr)
{
	char **user_command = NULL;
	char *token = NULL;
	size_t i = 0;
	int size = 0;

	if (lineptr == NULL)
		return (NULL);

	for (i = 0; lineptr[i]; i++)
	{
		if (lineptr[i] == ' ')
			size++;
	}
	if ((size + 1) == _strlen(lineptr))
		return (NULL);
	user_command = malloc(sizeof(char *) * (size + 2));
	if (user_command == NULL)
		return (NULL);

	token = strtok(lineptr, " \n\t\r");

	for (i = 0; token != NULL; i++)
	{
		user_command[i] = token;
		token = strtok(NULL, " \n\t\r");
	}
	user_command[i] = NULL;
	return (user_command);
}
