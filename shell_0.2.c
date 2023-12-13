#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 256
#define PROMPT "#cisfun$ "
#define MAX_ARGS 64
#define DELIMITERS " \t\r\n\a"

int main() {
    char cmd[MAX_CMD_LEN];
    char *argv[MAX_ARGS];
    pid_t pid;
    int status;
    size_t len;  /* Declare len at the start of the block */
    int argc;    /* Declare argc at the start of the block */

    while (1) {
        printf(PROMPT);

        if (!fgets(cmd, MAX_CMD_LEN, stdin)) {
            if (feof(stdin)) {
                printf("\n");
                exit(EXIT_SUCCESS);
            } else {
                perror("fgets");
                continue;
            }
        }

        len = strlen(cmd);
        if (len > 0 && cmd[len - 1] == '\n') {
            cmd[len - 1] = '\0';
        }

        argc = 0;
        argv[argc] = strtok(cmd, DELIMITERS);
        while (argv[argc] != NULL && argc < MAX_ARGS - 1) {
            argv[++argc] = strtok(NULL, DELIMITERS);
        }
        argv[argc] = NULL;

        if (argv[0] == NULL) {
            continue;
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            if (execvp(argv[0], argv) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
