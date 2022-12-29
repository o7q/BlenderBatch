#pragma once

#include <stdio.h>
#include <dirent.h>
#include "../utils.h"

void jobCreate(char blenderPath[])
{
    refresh();

    printf(" Job Name:\n -> ");
    char jobName[512];
    fgets(jobName, sizeof(jobName), stdin);
    omitNewLine(jobName);

    char jobDirectory[1024];
    sprintf(jobDirectory, "%s%s", "BlenderBatch\\_jobs\\", jobName);
    mkdir(jobDirectory);
    char jobChunk[2048];
    sprintf(jobChunk, "%s%s", jobDirectory, "\\_jobchunks");
    mkdir(jobChunk);

    int jobIndex = 0;
    while (1)
    {
        char scriptArgs[2048];

        printf("\n Blend File (! to exit):\n -> ");
        char blendfile[512];
        fgets(blendfile, sizeof(blendfile), stdin);
        omitNewLine(blendfile);

        if (blendfile[0] == '!') return;

        printf("\n Render As Sequence? (y or n):\n -> ");
        char renderMode[512];
        fgets(renderMode, sizeof(renderMode), stdin);
        omitNewLine(renderMode);

        if(renderMode[0] == 'y')
        {
            printf("\n Start Frame:\n -> ");
            char sframe[512];
            fgets(sframe, sizeof(sframe), stdin);
            omitNewLine(sframe);

            printf("\n End Frame:\n -> ");
            char eframe[512];
            fgets(eframe, sizeof(eframe), stdin);
            omitNewLine(eframe);

            sprintf(scriptArgs, "%s%s%s%s%s%s%s%d%s", " -s ", sframe, " -e ", eframe, " -a /e | tee-object 'BlenderBatch\\_jobs\\", jobName, "\\job@log", jobIndex, ".txt'\"");
        }
        else
        {
            printf("\n Frame:\n -> ");
            char frame[512];
            fgets(frame, sizeof(frame), stdin);
            omitNewLine(frame);

            sprintf(scriptArgs, "%s%s%s%s%s%d%s", " -f ", frame, " /e | tee-object 'BlenderBatch\\_jobs\\", jobName, "\\job@log", jobIndex, ".txt'\"");
        }

        char script[4096];
        sprintf(script, "%s%s%s%s%s", "powershell -command \"", blenderPath, " -b ", fixPath(blendfile, '\''), scriptArgs);

        char file[1024];
        sprintf(file, "%s%s%s%d", "BlenderBatch\\_jobs\\", jobName, "\\_jobchunks\\job@chunk", jobIndex);

        FILE* file_ptr = fopen(file, "w");
        fprintf(file_ptr, script);
        fclose(file_ptr);

        jobIndex++;
    }
}