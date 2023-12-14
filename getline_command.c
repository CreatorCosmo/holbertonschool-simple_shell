#include "shell.h"

char *_getline_command(void) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t linelen;

    if (isatty(STDIN_FILENO)) {
        /* Interactive terminal */
        /* Implement your interactive input handling here. */
        /* This could be a simple prompt followed by fgets or a more complex readline implementation. */
        printf("prompt> "); /* Example prompt */
        linelen = getline(&line, &bufsize, stdin); /* Using getline as an example */
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
            return NULL;
        } else {
            /* Handle getline errors */
            perror("getline");
            exit(EXIT_FAILURE); /* Or handle the error as per your requirement */
        }
    }

    return line;
}

