#include "shell.h"

/**
 * _get_path - Retrieves the PATH environment variable.
 * @env: Environment variables
 * Return: The value of PATH
 */
 
 void _getenv(char **env) {
    int i = 0;
    while (env[i] != NULL) {
        printf("%s\n", env[i]);
        i++;
    }
}
char *_get_path(char **env) {
    size_t index = 0;
    char *path = NULL;

    while (env[index] != NULL) {
        if (_strncmp(env[index], "PATH=", 5) == 0) {
            path = strdup(env[index] + 5);
            break;
        }
        index++;
    }

    return path;
}

/**
 * _values_path - Parses the PATH variable to find the full path of a command.
 * @arg: The command to find
 * @env: Environment variables
 * Return: 0 on success, -1 on failure
 */
int _values_path(char **arg, char **env) {
    char *path = _get_path(env);
    char *token = NULL;
    struct stat stat_buf;
    char *full_path = NULL;

    if (path == NULL) {
        return -1;
    }

    token = strtok(path, ":");
    while (token != NULL) {
        full_path = malloc(strlen(token) + strlen(*arg) + 2);
        if (full_path == NULL) {
            free(path);
            return -1;
        }
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, *arg);

        if (stat(full_path, &stat_buf) == 0) {
            free(*arg);
            *arg = full_path;
            free(path);
            return 0;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path);
    return -1;
}

