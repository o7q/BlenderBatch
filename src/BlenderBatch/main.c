#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <dirent.h>
#include <stdbool.h>
#include "includes\processors\wizard.h"
#include "includes\processors\render.h"
#include "includes\utils.h"

char blenderPath[512];

int main(void)
{
    char titleScript[32];
    sprintf(titleScript, "%s%s", "title BlenderBatch ", version);
    system(titleScript);

    refresh();

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

    while(1)
    {
        refresh();

        FILE *blenderPath_read = fopen("BlenderBatch\\cfg@blenderPath", "r");

        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), blenderPath_read) != NULL) strcpy(blenderPath, buffer);
        fclose(blenderPath_read);

        printf(" Select a job by typing its name (create one by typing !, delete one by typing @<JOBNAME>)\n");

        // display created jobs
        DIR *dir = opendir("BlenderBatch\\_jobs");
        if (dir)
        {
            struct dirent* entry;
            while ((entry = readdir(dir)) != NULL)
            {
                // exclude "." and ".."
                if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
                printf(" >> %s\n", entry->d_name);
            }
            closedir(dir);
        }

        printf(" -> ");

        char select[512];
        fgets(select, sizeof(select), stdin);
        omitNewLine(select);

        if (select[0] == '!') jobCreate(blenderPath);
        else if (select[0] == '@')
        {
            char *pIndex;
            while ((pIndex = strchr(select, '@')) != NULL) memmove(pIndex, pIndex + 1, strlen(pIndex));
            char jobDel[1024];
            sprintf(jobDel, "%s%s%s", "rmdir \"BlenderBatch\\_jobs\\", select, "\" /s /q 2> nul");
            system(jobDel);
        }
        else jobRender(select);
    }

    return 0;
}