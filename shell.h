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

/* Function prototypes for built-in commands */
int shell_ctrld(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_ls(char **args); /* Prototype for shell_ls */

extern char **environ;

/* Utility function prototypes */
int _strcmp(char *s1, char *s2);
size_t _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _putchar(char c);

char *_get_path(char **env);
int _values_path(char **arg, char **env);
char *_getline_command(void);
void _getenv(char **env);
char **tokenize(char *lineptr);
void _exit_command(char **args, char *lineptr, int _exit);
int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c);

#endif /* SHELL_H */

