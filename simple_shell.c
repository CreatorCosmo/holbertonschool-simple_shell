#include "shell.h"

void execute_command(char *cmd) {
	pid_t pid;
	int status;
	char *argv[2];
	char *trimmed_cmd;
	trimmed_cmd = trim(cmd);

	if (trimmed_cmd == NULL || strlen(trimmed_cmd) == 0) {
		free(trimmed_cmd);
		return;
	}
	argv[0] = trimmed_cmd;
	argv[1] = NULL;

	if ((pid = fork()) == -1) {
		perror("Error");
		free(trimmed_cmd);
		return;
	}
	if (pid == 0) {
		if (execve(trimmed_cmd, argv, NULL) == -1) {
			perror(trimmed_cmd);
		}
		exit(EXIT_FAILURE);
	} else {
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(trimmed_cmd);
}

int main(void) {
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1) {
		printf("#cisfun$ ");
		fflush(stdout);
		read = getline(&line, &len, stdin);
		if (read == -1) {
			if (feof(stdin)) {
				printf("\n");
				break;
			} else {
				perror("getline");
				continue;
			}
		}
		line[read - 1] = '\0';
		execute_command(line);
	}
	free(line);
	return 0;
}
