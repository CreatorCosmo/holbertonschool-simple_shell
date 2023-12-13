#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *trim(char *str) {
	char *end;
	while(isspace((unsigned char)*str)) str++;
	if(*str == 0) {
		return strdup("");
	}
	end = str + strlen(str) - 1;
	while(end > str && isspace((unsigned char)*end)) end--;
	end[1] = '\00';
	return strdup(str);
}
