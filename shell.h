#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* String manipulation functions */
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(const char *s);
size_t _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);

/* Tokenization function */
char **tokenize(char *lineptr);

/* Environment functions */
char *_getenv(char **env, const char *name);
void env_functions(char **env);
int _values_path(char **arg, char **env);

/* Main shell function */
int _fork_fun(char **commands, char **av, char **env, char *line, int pathValue, int is_path);

char *_getline_command(void);

#endif /* SHELL_H */
