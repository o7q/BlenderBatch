#pragma once

#include "../utils.h"

void jobCreate(char jobName[], char blenderPath[])
{
    refresh();

    char jobDirectory[631];
    sprintf(jobDirectory, "%s%s", "BlenderBatch\\_jobs\\", jobName);
    mkdir(jobDirectory);
    char jobChunk[642];
    sprintf(jobChunk, "%s%s", jobDirectory, "\\_jobchunks");
    mkdir(jobChunk);

    int jobIndex = 0;
    while (1)
    {
        char scriptArgs[1708];

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

        char chunk_script[1733];
        sprintf(chunk_script, "%s%s%s%s%s", "powershell -command \"", blenderPath, " -b ", fixPath(blendfile, '\''), scriptArgs);

        char chunk_export[662];
        sprintf(chunk_export, "%s%s%s%d", "BlenderBatch\\_jobs\\", jobName, "\\_jobchunks\\job@chunk", jobIndex);

        FILE *chunk_ptr = fopen(chunk_export, "w");
        fprintf(chunk_ptr, chunk_script);
        fclose(chunk_ptr);

        jobIndex++;
    }
}