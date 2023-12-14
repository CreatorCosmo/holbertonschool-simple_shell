#include "shell.h"

char *_getline_command(void) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t linelen;

    if (isatty(STDIN_FILENO)) {
        /* Interactive terminal */
        printf("prompt> "); /* Display a prompt in interactive mode */
        linelen = getline(&line, &bufsize, stdin);
    } else {
        /* Non-interactive input (like from a pipe or file redirection) */
        linelen = getline(&line, &bufsize, stdin);
    }

    if (linelen == -1) {
        if (feof(stdin)) {
            /* End-of-file reached, handle accordingly */
            if (line) {
                free(line);
            }
            return NULL; /* Return NULL to indicate EOF */
        } else {
            perror("getline");
            exit(EXIT_FAILURE); /* Exit or handle the error as required */
        }
    }

    return line; /* Return the line read from input */
}

