#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#define MAX_CMD_LEN 256
#define PROMPT "#cisfun$ "
#define DELIMITERS " \\t\\r\\n\\a"

int main() {
    char cmd[MAX_CMD_LEN];
    char *argv[64];
    int status;
    size_t len;
    int argc; /* Declare argc here */

    while (1) {
        printf(PROMPT);

        if (!fgets(cmd, MAX_CMD_LEN, stdin)) {
            if (feof(stdin)) {
                printf("\\n");
                break;
            } else {
                perror("fgets");
                continue;
            }
        }

        len = strlen(cmd);
        if (len > 0 && cmd[len - 1] == '\n') {
            cmd[len - 1] = '\0';
        }

        argc = 0; /* Initialize argc here */
        argv[argc] = strtok(cmd, DELIMITERS);
        while (argv[argc] != NULL) {
            argv[++argc] = strtok(NULL, DELIMITERS);
        }

        if (argv[0] == NULL) {
            continue;
        }

        if (fork() == 0) {
            if (execvp(argv[0], argv) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            wait(&status);
        }
    }

    return 0;
}
