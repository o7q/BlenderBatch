#pragma once

#include <iostream>
#include "Draw.hpp"
#include "Files.hpp"
#include "Strings.hpp"

void CreateTask(std::string taskName, std::string blenderPath);

void CreateTask(std::string taskName, std::string blenderPath)
{
	CreateFolder("BlenderBatch\\tasks\\" + taskName);

	int taskIndex = 0;
	bool displayFinish = false;

	while (true)
	{
		RefreshScreen();

		std::string workingPath = "BlenderBatch\\tasks\\" + taskName + "\\" + std::to_string(taskIndex);

		CreateFolder(workingPath);

		std::cout << "\n Blend File:" << (displayFinish ? " (type ! to finish setup)" : "") << "\n";
		DrawCursor();
		std::string blendFile = "";
		getline(std::cin, blendFile);

		blendFile = RemoveCharacter(blendFile, '"');
		WriteFile(workingPath + "\\blendFile", blendFile);

		if (blendFile[0] == '!')
			return;

		std::cout << "\n Render Engine (cycles, eevee, workbench, povray, or type ! to use project settings):\n";
		DrawCursor();
		std::string renderEngine = "";
		getline(std::cin, renderEngine);
		if (renderEngine[0] != '!')
			WriteFile(workingPath + "\\renderEngine", renderEngine);

		std::cout << "\n Render Animation? (y or n):\n";
		DrawCursor();
		std::string renderMode = "";
		getline(std::cin, renderMode);
		WriteFile(workingPath + "\\renderMode", renderMode);

		if (renderMode[0] == 'y')
		{
			std::cout << "\n Start Frame:\n";
			DrawCursor();
			std::string startFrame = "";
			getline(std::cin, startFrame);
			WriteFile(workingPath + "\\startFrame", startFrame);

			std::cout << "\n End Frame:\n";
			DrawCursor();
			std::string endFrame = "";
			getline(std::cin, endFrame);
			WriteFile(workingPath + "\\endFrame", endFrame);
		}

		displayFinish = true;
	}
}