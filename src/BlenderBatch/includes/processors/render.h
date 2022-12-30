#pragma once

#include "../utils.h"

void jobRender(char job[])
{
    refresh();

    // initialize render jobs
    char jobPath[512];
    sprintf(jobPath, "%s%s%s", "BlenderBatch\\_jobs\\", job, "\\_jobchunks\\");
    DIR *jobDir = opendir(jobPath);
    if (jobDir)
    {
        // count the amount of chunks
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
            char jobChunk[632];
            sprintf(jobChunk, "%s%s%d", jobPath, "\\job@chunk", chunkIndex);

            FILE *blenderPath_read = fopen(jobChunk, "r");

            // read job chunk into buffer
            char chunkBuffer[512];
            char chunkScript[512];
            if (fgets(chunkBuffer, sizeof(chunkBuffer), blenderPath_read) != NULL) strcpy(chunkScript, chunkBuffer);
            fclose(blenderPath_read);

            printf("\n\n STARTING RENDER OF JOB CHUNK #%d\n\n", chunkIndex);

            system(chunkScript);

            chunkIndex++;
        }

        closedir(jobDir);
    }

    printf("\n\n Render Finished! (all errors, if any, have been displayed)\n ");
    system("pause");
}