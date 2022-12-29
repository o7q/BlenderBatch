#pragma once

#include <stdio.h>
#include <dirent.h>

void jobRender(char job[])
{
    refresh();

    // initialize render jobs
    char jobPath[1024];
    sprintf(jobPath, "%s%s%s", "BlenderBatch\\_jobs\\", job, "\\_jobchunks\\");
    DIR *jobDir = opendir(jobPath);
    if (jobDir)
    {
        int jobIndex = 0;
        struct dirent *jobEntry;
        while ((jobEntry = readdir(jobDir)) != NULL)
        {
            if (jobEntry->d_name[0] == '.') continue;
            jobIndex++;
        }

        // execute render jobs
        int chunkIndex = 0;
        for (int i = 0; i < jobIndex; i++)
        {
            char jobChunk[2048];
            sprintf(jobChunk, "%s%s%d", jobPath, "\\job@chunk", chunkIndex);

            FILE *blenderPath_read = fopen(jobChunk, "r");

            char chunkBuffer[1024];
            char chunkScript[512];
            if (fgets(chunkBuffer, sizeof(chunkBuffer), blenderPath_read) != NULL) strcpy(chunkScript, chunkBuffer);
            fclose(blenderPath_read);

            printf(" STARTING RENDER OF CHUNK #%d\n\n", chunkIndex);

            system(chunkScript);

            chunkIndex++;
        }

        closedir(jobDir);
    }

    printf("\n\n Render Finished!\n ");
    system("pause");
}