#pragma once

#include "../utils.h"

void jobCreate(char jobName[], char blenderPath[])
{
    refresh();

    int displayFinish = 0;

    char jobDirectory[512];
    sprintf(jobDirectory, "%s%s", "BlenderBatch\\_jobs\\", jobName);
    mkdir(jobDirectory);

    char jobChunk[623];
    sprintf(jobChunk, "%s%s", jobDirectory, "\\_jobchunks");
    mkdir(jobChunk);

    int jobIndex = 0;
    while (1)
    {
        char scriptArgs[1712];

        printf("\n Blend File%s:\n", displayFinish == 1 ? " (type ! to finish setup)" : "");
        drawCur();
        char blendfile[512];
        fgets(blendfile, sizeof(blendfile), stdin);
        omitNewLine(blendfile);

        // exit if '!' is typed
        if (blendfile[0] == '!') return;

        printf("\n Render Engine (cycles, eevee, workbench, povray):\n");
        drawCur();
        char renderEngine[512];
        fgets(renderEngine, sizeof(renderEngine), stdin);
        omitNewLine(renderEngine);

        if (strcmp(renderEngine, "cycles") == 0) sprintf(renderEngine, "%s", "CYCLES");
        if (strcmp(renderEngine, "eevee") == 0) sprintf(renderEngine, "%s", "BLENDER_EEVEE");
        if (strcmp(renderEngine, "workbench") == 0) sprintf(renderEngine, "%s", "BLENDER_WORKBENCH");
        if (strcmp(renderEngine, "povray") == 0) sprintf(renderEngine, "%s", "POVRAY_RENDER");

        printf("\n Render As Sequence? (type y or n):\n");
        drawCur();
        char renderMode[512];
        fgets(renderMode, sizeof(renderMode), stdin);
        omitNewLine(renderMode);

        if(renderMode[0] == 'y')
        {
            // configure job chunk for sequence
            printf("\n Start Frame:\n");
            drawCur();
            char sframe[512];
            fgets(sframe, sizeof(sframe), stdin);
            omitNewLine(sframe);

            printf("\n End Frame:\n");
            drawCur();
            char eframe[512];
            fgets(eframe, sizeof(eframe), stdin);
            omitNewLine(eframe);

            sprintf(scriptArgs, "%s%s%s%s%s%s%s%s%s%d%s", " -E ", renderEngine, " -s ", sframe, " -e ", eframe, " -a /e | tee-object 'BlenderBatch\\_jobs\\", jobName, "\\job@chunk", jobIndex, ".log'\"");
        }
        else
        {
            // configure job chunk for single frame
            printf("\n Frame:\n");
            drawCur();
            char frame[512];
            fgets(frame, sizeof(frame), stdin);
            omitNewLine(frame);

            sprintf(scriptArgs, "%s%s%s%s%s%s%s%d%s", " -E ", renderEngine, " -f ", frame, " /e | tee-object 'BlenderBatch\\_jobs\\", jobName, "\\job@chunk", jobIndex, ".log'\"");
        }

        // configure job chunk content
        char chunk_script[1837];
        sprintf(chunk_script, "%s%s%s%s%s", "powershell -command \"", blenderPath, " -b ", fixPath(blendfile, '\''), scriptArgs);

        // configure job chunk export
        char chunk_export[512];
        sprintf(chunk_export, "%s%s%s%d", "BlenderBatch\\_jobs\\", jobName, "\\_jobchunks\\job@chunk", jobIndex);

        // write job chunk
        FILE *chunk_ptr = fopen(chunk_export, "w");
        fprintf(chunk_ptr, chunk_script);
        fclose(chunk_ptr);

        jobIndex++;
        displayFinish = 1;

        refresh();
    }
}