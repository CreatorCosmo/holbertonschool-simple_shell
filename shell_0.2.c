#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

#define MAX_CMD_LEN 256
#define PROMPT "#cisfun$ "

int main() {
	char cmd[MAX_CMD_LEN];
	char *argv[2]; // only the command and NULL
	argv[1] = NULL;

	while (1) {
		printf(PROMPT);
		if (!fgets(cmd, MAX_CMD_LEN, stdin)) {
			if (feof(stdin)) { // handle EOF
				printf("\\n");
				break;
			} else {
				perror("fgets");
				continue;
			}
		}

		size_t len = strlen(cmd);
		if (len > 0 && cmd[len - 1] == '\\n') {
			cmd[len - 1] = '\\0'; // remove newline character
		}

		argv[0] = cmd; // set the command

		if (fork() == 0) { // create a child process
			// Child process: try to execute the command
			if (execve(cmd, argv, NULL) == -1) {
				perror(cmd);
				exit(EXIT_FAILURE);
			}
		} else {
			// Parent process: wait for the child to complete
			wait(NULL);
		}
	}

	return 0;
}
