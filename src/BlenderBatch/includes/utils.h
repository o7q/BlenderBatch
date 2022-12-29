#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fixPath(char path[], char sep)
{
    char *pIndex;
    while ((pIndex = strchr(path, '"')) != NULL) memmove(pIndex, pIndex + 1, strlen(pIndex));

    char *path_fix = (char*) malloc(sizeof(char) * (strlen(path) + 4));
    snprintf(path_fix, strlen(path) + 4, "%c%s%c", sep, path, sep);

    return path_fix;
}

char* omitNewLine(char in[])
{
    char *p = strchr(in, '\n');
    if (p) *p = '\0'; else return NULL;
    return in;
}