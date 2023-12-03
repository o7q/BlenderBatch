#pragma once

#include <iostream>
#include "Draw.hpp"
#include "Files.hpp"
#include "Strings.hpp"

void CreateTask(const std::string& taskName, const std::string& blenderPath);

void CreateTask(const std::string& taskName, const std::string& blenderPath)
{
	CreateFolder("BlenderBatch\\tasks\\" + taskName);
	CreateFolder("BlenderBatch\\tasks\\" + taskName + "\\_queue");
	CreateFolder("BlenderBatch\\tasks\\" + taskName + "\\logs");

	int taskIndex = 0;
	bool displayFinish = false;

	while (true)
	{
		RefreshScreen();

		std::cout << "\n Blend File (drag 'n drop)" << (displayFinish ? " OR (press enter to finish setup):" : ":") << "\n";
		DrawCursor();
		std::string blendFile = "";
		getline(std::cin, blendFile);

		blendFile = RemoveCharacter(blendFile, '"');

		if (blendFile == "")
			return;

		std::cout << "\n Render Engine (cycles, eevee, workbench, or press enter to use project settings):\n";
		DrawCursor();
		std::string renderEngine = "";
		getline(std::cin, renderEngine);
		if (renderEngine == "cycles") renderEngine = "CYCLES";
		if (renderEngine == "eevee") renderEngine = "BLENDER_EEVEE";
		if (renderEngine == "workbench") renderEngine = "BLENDER_WORKBENCH";
		if (renderEngine == "") renderEngine = "__PROJECT__";

		std::cout << "\n Render Animation? (y or n):\n";
		DrawCursor();
		std::string renderMode = "";
		getline(std::cin, renderMode);
		if (renderMode[0] == 'y')
			renderMode = "__ANIMATION__";
		else
			renderMode = "__FRAME__";

		std::string startFrame = "__IGNORE__";
		std::string endFrame = "__IGNORE__";
		if (renderMode == "__ANIMATION__")
		{
			std::cout << "\n Start Frame:\n";
			DrawCursor();
			getline(std::cin, startFrame);

			std::cout << "\n End Frame:\n";
			DrawCursor();
			getline(std::cin, endFrame);
		}
		else
		{
			std::cout << "\n Frame:\n";
			DrawCursor();
			getline(std::cin, startFrame);
		}

		std::string taskFile =
			"BLEND_FILE¶" + blendFile + "\n" +
			"RENDER_ENGINE¶" + renderEngine + "\n" +
			"RENDER_MODE¶" + renderMode + "\n" +
			"START_FRAME¶" + startFrame + "\n" +
			"END_FRAME¶" + endFrame;

		std::string taskFilePath = "BlenderBatch\\tasks\\" + taskName + "\\_queue\\" + std::to_string(taskIndex) + ".bbq";
		WriteFile(taskFilePath, taskFile);

		taskIndex++;
		displayFinish = true;
	}
}