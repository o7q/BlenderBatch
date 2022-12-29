#include "includes\utils.h"
#include "includes\processors\wizard.h"
#include "includes\processors\render.h"

char blenderPath[614];

// NOTE FOR MYSELF: string sizes have 100 added to their minimum overflow limit

int main(void)
{
    char titleScript[64];
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

        char buffer[614];
        if (fgets(buffer, sizeof(buffer), blenderPath_read) != NULL) strcpy(blenderPath, buffer);
        fclose(blenderPath_read);

        printf(" Select a render job by typing its name (create one by typing !<JOBNAME>, delete one by typing @<JOBNAME>)\n");

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

        char select[64];
        fgets(select, sizeof(select), stdin);
        omitNewLine(select);

        if (select[0] == '!')
        {
            omitChar(select, '!');     
            jobCreate(select, blenderPath);
        }
        else if (select[0] == '@')
        {
            omitChar(select, '@'); 
            char jobPurge[204];
            sprintf(jobPurge, "%s%s%s", "rmdir \"BlenderBatch\\_jobs\\", select, "\" /s /q 2> nul");
            system(jobPurge);
        }
        else jobRender(select);
    }

    return 0;
}