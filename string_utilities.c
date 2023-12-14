#include "shell.h"

int _strcmp(char *s1, char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

size_t _strncmp(char *s1, char *s2, size_t n) {
    if (n == 0) return 0;

    while (n-- != 0 && *s1 && *s1 == *s2) {
        s1++;
        s2++;
        if (n == 0 || *s1 == '\0' || *s2 == '\0') break;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int _strlen(char *s) {
    int length = 0;
    while (*s++) length++;
    return length;
}

char *_strcpy(char *dest, const char *src) {
    char *save = dest;
    while ((*dest++ = *src++));
    return save;
}

char *_strcat(char *dest, const char *src) {
    char *save = dest;
    while (*dest) dest++;
    while ((*dest++ = *src++));
    return save;
}

