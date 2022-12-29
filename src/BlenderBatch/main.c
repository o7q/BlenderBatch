#include "includes\utils.h"
#include "includes\processors\wizard.h"
#include "includes\processors\render.h"

// NOTE FOR MYSELF: string sizes have 100 added to their minimum overflow size
char blenderPath[614];

int main(void)
{
    char titleScript[64];
    sprintf(titleScript, "%s%s", "title BlenderBatch ", version);
    system(titleScript);

    refresh();

    // create root directories
    mkdir("BlenderBatch");
    mkdir("BlenderBatch\\_jobs");
    // if blender is not configured prompt the user to do so
    if ((_access("BlenderBatch\\cfg@blenderPath", 0)) == -1)
    {
        printf(" Blender Path:\n");
        drawCur();
        char blenderPathIn[512];
        fgets(blenderPathIn, sizeof(blenderPathIn), stdin);
        omitNewLine(blenderPathIn);

        // remove user double-quotes and replace them with proper ones (if they didn't use them correctly)
        strcpy(blenderPath, fixPath(blenderPathIn, '"'));

        // write blender path config
        FILE *blenderPath_write = fopen("BlenderBatch\\cfg@blenderPath", "w");
        fprintf(blenderPath_write, blenderPath);
        fclose(blenderPath_write);
    }

    // job interface
    bool persistent = true;
    while(persistent)
    {
        refresh();

        FILE *blenderPath_read = fopen("BlenderBatch\\cfg@blenderPath", "r");

        char buffer[614];
        if (fgets(buffer, sizeof(buffer), blenderPath_read) != NULL) strcpy(blenderPath, buffer);
        fclose(blenderPath_read);

        printf(" Select a render job by typing its name\n - Create one by typing !<JOBNAME>\n - Delete one by typing @<JOBNAME>\n - Type # to exit\n\n");

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

        drawCur();

        char select[64];
        fgets(select, sizeof(select), stdin);
        omitNewLine(select);

        if (select[0] == '!')
        {
            // create new job
            omitChar(select, '!');     
            jobCreate(select, blenderPath);
        }
        else if (select[0] == '@')
        {
            // purge job
            omitChar(select, '@'); 
            char jobPurge[204];
            sprintf(jobPurge, "%s%s%s", "rmdir \"BlenderBatch\\_jobs\\", select, "\" /s /q 2> nul");
            system(jobPurge);
        }
        else if (select[0] == '#') /* exit program */ persistent = false;
        else /* render job */ jobRender(select);
    }

    return 0;
}