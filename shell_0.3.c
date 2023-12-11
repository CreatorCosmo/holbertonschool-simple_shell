#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#define MAX_CMD_LEN 256
#define PROMPT "#cisfun$ "
#define DELIMITERS " \\t\\r\\n\\a"

char *find_command_in_path(const char *cmd) {
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token;
	char *full_cmd;

	for (token = strtok(path_copy, ":"); token != NULL; token = strtok(NULL, ":")) {
		full_cmd = malloc(strlen(token) + strlen(cmd) + 2);
		sprintf(full_cmd, "%s/%s", token, cmd);

		if (access(full_cmd, X_OK) == 0) {
			free(path_copy);
			return full_cmd; /* Caller must free this */
		}

		free(full_cmd);
	}

	free(path_copy);
	return NULL;
}

int main() {
	char cmd[MAX_CMD_LEN];
	char *argv[64];
	int status;
	size_t len;
	int argc;
	char *full_cmd_path;

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

		argc = 0;
		argv[argc] = strtok(cmd, DELIMITERS);
		while (argv[argc] != NULL) {
			argv[++argc] = strtok(NULL, DELIMITERS);
		}

		if (argv[0] == NULL) {
			continue;
		}

		full_cmd_path = find_command_in_path(argv[0]);
		if (full_cmd_path == NULL) {
			fprintf(stderr, "%s: command not found\n", argv[0]);
			continue;
		}

		if (fork() == 0) {
			if (execvp(full_cmd_path, argv) == -1) {
				perror(full_cmd_path);
				free(full_cmd_path);
				exit(EXIT_FAILURE);
			}
		} else {
			wait(&status);
		}

		free(full_cmd_path);
	}

	return 0;
}

