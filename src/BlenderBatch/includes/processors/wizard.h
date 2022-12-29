#pragma once

#include <stdio.h>
#include <dirent.h>
#include "../utils.h"

void jobWizard(char blenderPath[])
{
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
    bool persistent = true;
    while (persistent)
    {
        printf(" Blend File:\n -> ");
        char blendfile[512];
        fgets(blendfile, sizeof(blendfile), stdin);
        omitNewLine(blendfile);

        printf(" Start Frame:\n -> ");
        char sframe[512];
        fgets(sframe, sizeof(sframe), stdin);
        omitNewLine(sframe);

        printf(" End Frame:\n -> ");
        char eframe[512];
        fgets(eframe, sizeof(eframe), stdin);
        omitNewLine(eframe);

        char file[1024];
        sprintf(file, "%s%s%s%d", "BlenderBatch\\_jobs\\", jobName, "\\_jobchunks\\job@chunk", jobIndex);

        char script[2048];
        sprintf(script, "%s%s%s%s%s%s%s%s%s%s%s%d%s", "powershell -command \"", blenderPath, " -b ", fixPath(blendfile, '\''), " -s ", sframe, " -e ", eframe, " -a /e | tee-object 'BlenderBatch\\_jobs\\", jobName, "\\job@log", jobIndex, ".txt'\"");

        FILE* file_ptr = fopen(file, "w");
        fprintf(file_ptr, script);
        fclose(file_ptr);

        jobIndex++;
    }
}