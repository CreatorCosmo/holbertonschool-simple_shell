#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Function Declarations */
char *_getline_command(void);
char **tokenize(char *lineptr);
int _strcmp(char *s1, char *s2);
size_t _strncmp(char *s1, char *s2, size_t n);  /* Declaration for _strncmp */
void _getenv(char **env);
int _values_path(char **arg, char **env);
int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c);

/* Add other function declarations as needed */

#endif /* SHELL_H */

