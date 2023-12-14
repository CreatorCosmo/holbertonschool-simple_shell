#include "shell.h"

/**
 * tokenize - Breaks a string into tokens based on delimiters.
 * @lineptr: The input string to be tokenized.
 * Return: An array of string tokens.
 */
char **tokenize(char *lineptr) {
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "tokenize: allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* Using a space as a delimiter for tokenization */
    token = strtok(lineptr, " \t\r\n\a");
    while (token != NULL) {
        tokens[position++] = token;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "tokenize: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

