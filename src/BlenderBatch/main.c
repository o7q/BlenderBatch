#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <dirent.h>
#include <stdbool.h>
#include "includes\processors\wizard.h"
#include "includes\processors\render.h"
#include "includes\utils.h"

char version[] = "v1.0.0";
char blenderPath[512];

int main(void)
{
    char titleScript[32];
    sprintf(titleScript, "%s%s", "title BlenderBatch ", version);
    system(titleScript);

    mkdir("BlenderBatch");
    mkdir("BlenderBatch\\_jobs");
    if ((_access("BlenderBatch\\cfg@blenderPath", 0)) == -1)
    {
        printf(" Blender Path:\n -> ");
        char blenderPathIn[512];
        gets(blenderPathIn);

        strcpy(blenderPath, fixPath(blenderPathIn, '"'));

        FILE *blenderPath_write = fopen("BlenderBatch\\cfg@blenderPath", "w");
        fprintf(blenderPath_write, blenderPath);
        fclose(blenderPath_write);
    }

    FILE *blenderPath_read = fopen("BlenderBatch\\cfg@blenderPath", "r");

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), blenderPath_read) != NULL) strcpy(blenderPath, buffer);
    fclose(blenderPath_read);

    printf(" Select a job or create a new one by typing !\n");

    // display created jobs
    DIR *dir = opendir("BlenderBatch\\_jobs");
    if (dir)
    {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL)
        {
            // exclude "." and ".."
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
            printf("  > %s\n", entry->d_name);
        }
        closedir(dir);
    }

    printf(" -> ");

    char select[512];
    fgets(select, sizeof(select), stdin);
    omitNewLine(select);

    if (select[0] == '!') jobWizard(blenderPath); else renderJob(select);

    return 0;
}