#include "shell.h"

char *_getline_command(void) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t linelen;

    if (isatty(STDIN_FILENO)) {
        /* Interactive terminal */
        /* This could be a simple prompt followed by getline */
        printf("prompt> ");
        linelen = getline(&line, &bufsize, stdin);
    } else {
        /* Non-interactive input (like from a pipe or file redirection) */
        linelen = getline(&line, &bufsize, stdin);
    }

    if (linelen == -1) {
        if (feof(stdin)) {
            /* End-of-file reached, handle accordingly */
            if (line != NULL) {
                free(line);
            }
            return NULL;
        } else {
            /* Handle getline errors */
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

