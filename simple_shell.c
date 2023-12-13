#include "shell.h"

void execute_command(char *cmd) {
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	if ((pid = fork()) == -1) {
		perror("Error");
		return;
	}
	if (pid == 0) {
		if (execve(cmd, argv, NULL) == -1) {
			perror(cmd);
		}
		exit(EXIT_FAILURE);
	} else {
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

int main(void) {
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1) {
		printf("#cisfun$ ");
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
