#include "shell.h"
#include <ctype.h> /* Include ctype.h for isspace function */

/* Function prototypes for built-in commands */
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_ctrld(char **args);
int shell_ls(char **args);

/* Array of strings representing built-in command names. */
char *builtin_str[] = {"cd", "help", "exit", "^D", "ls"};

/* Array of function pointers corresponding to the built-in command functions */
int (*builtin_func[]) (char **) = {&shell_cd, &shell_help, &shell_exit, &shell_ctrld, &shell_ls};

/* shell_num_builtins - Returns the number of built-in commands */
int shell_num_builtins(void)
{
    return (sizeof(builtin_str) / sizeof(char *));
}

/* Implementations of built-in functions: */

/**
 * shell_cd - Changes the current directory
 * @args: Array of arguments. args[0] is "cd". args[1] is the directory to change to.
 * Return: 1 on success
 */
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

/**
 * shell_help - Displays help information for the shell
 * @args: Array of arguments. Not used in this function.
 * Return: Always returns 1 to continue execution.
 */
int shell_help(char **args)
{
    int i;

    printf("Oscar Bedat and Andres Henderson\n");
    printf("If you need help, call 1-800-help\n");
    (void)args;
    for (i = 0; i < shell_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    return (1);
}

/**
 * shell_exit - Exits the shell
 * @args: Array of arguments. Not used in this function.
 * Return: Always returns 0 to terminate execution.
 */
int shell_exit(char **args)
{
    (void)args;
    free(args);
    return (200);
}

/**
 * shell_ctrld - Handles "^D" input (end-of-transmission)
 * @args: Array of arguments. Not used in this function.
 * Return: Always returns 0 to terminate execution.
 */
int shell_ctrld(char **args)
{
    (void)args;
    free(args);
    return (200);
}
/**
 * shell_ls - Placeholder for the 'ls' command
 * @args: Array of arguments. Not used in this function.
 * Return: Always returns 1 to continue execution.
 */
int shell_ls(char **args)
{
    printf("'ls' is not a built-in command in this shell.\n");
    (void)args;
    return (1);
}

/* Helper function to trim whitespace from a string */
char *trim_whitespace(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
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

