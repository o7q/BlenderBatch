#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

char version[] = "v1.0.0";

char *omitChar(char in[], char charIn)
{
    // remove specified character from string
    char *pIndex;
    while ((pIndex = strchr(in, charIn)) != NULL) memmove(pIndex, pIndex + 1, strlen(pIndex));
    return in;
}

char *omitNewLine(char in[])
{
    // remove \n
    char *p = strchr(in, '\n');
    if (p) *p = '\0'; else return NULL;
    return in;
}

char *fixPath(char path[], char sep)
{
    // remove user double-quotes
    omitChar(path, '"'); 

    // add double-quotes around the path
    char *path_fix = (char *) malloc(sizeof(char) * (strlen(path) + 4));
    snprintf(path_fix, strlen(path) + 4, "%c%s%c", sep, path, sep);

    return path_fix;
}

void drawCur()
{
    // draw cursor
    printf(" -> ");
}

void refresh()
{
    // clear screen
    system("cls");
    printf("  ___ _             _         ___       _      _    \n"
           " | _ ) |___ _ _  __| |___ _ _| _ ) __ _| |_ __| |_  \n"
           " | _ \\ / -_) ' \\/ _` / -_) '_| _ \\/ _` |  _/ _| ' \\ %s\n"
           " |___/_\\___|_||_\\__,_\\___|_| |___/\\__,_|\\__\\__|_||_| %s\n\n", version, "by o7q");
}