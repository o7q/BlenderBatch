#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "Draw.hpp"
#include "Global.hpp"

namespace fs = std::filesystem;

void StartRenderTask(std::string taskName, std::string blenderPath)
{
	RefreshScreen();

	std::vector<std::string> tasks;

	std::string task = "BlenderBatch\\tasks\\" + taskName;
	std::string queueFile = task + "\\_queue";

	try
	{
		if (fs::exists(queueFile) && fs::is_directory(queueFile))
		{
			// iterate over the contents of the directory
			for (const auto& entry : fs::directory_iterator(queueFile))
			{
				// check if the entry is a regular file
				if (fs::is_regular_file(entry.path()))
					tasks.push_back(entry.path().string());
			}
		}
		else
			std::cout << " Directory does not exist or is not a valid directory." << std::endl;
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << " Error loading subtasks: " << e.what() << std::endl;
		std::getchar();
		return;
	}

	for (int i = 0; i < tasks.size(); i++)
	{
		QueueConfig queueData;

		std::string subtaskString = ReadFile(tasks[i]);
		std::vector subtask = SplitString(subtaskString, '\n');

		for (int j = 0; j < subtask.size(); j++)
		{
			std::vector subtaskSplit = SplitString(subtask[j], '¶');
			if (subtaskSplit[0] == "BLEND_FILE") queueData.BLEND_FILE = subtaskSplit[1];
			if (subtaskSplit[0] == "RENDER_ENGINE") queueData.RENDER_ENGINE = subtaskSplit[1];
			if (subtaskSplit[0] == "RENDER_MODE") queueData.RENDER_MODE = subtaskSplit[1];
			if (subtaskSplit[0] == "START_FRAME") queueData.START_FRAME = subtaskSplit[1];
			if (subtaskSplit[0] == "END_FRAME") queueData.END_FRAME = subtaskSplit[1];
		}

		std::string renderScript = "";
		std::string engineScript = "";
		if (queueData.RENDER_ENGINE != "__PROJECT__")
			engineScript = "-E " + queueData.RENDER_ENGINE + " ";

		if (queueData.RENDER_MODE == "__ANIMATION__")
			renderScript = "powershell -command \"\"" + blenderPath + "\" -b '" + queueData.BLEND_FILE + "' " + engineScript + "-s " + queueData.START_FRAME + " -e " + queueData.END_FRAME + " -a /e | tee-object '" + task + "\\logs\\" + std::to_string(i) + ".log'\"";
		else
			renderScript = "powershell -command \"\"" + blenderPath + "\" -b '" + queueData.BLEND_FILE + "' " + engineScript + "-f " + queueData.START_FRAME + " /e | tee-object '" + task + "\\logs\\" + std::to_string(i) + ".log'\"";

		system(renderScript.c_str());
	}

	std::cout << "\n\n The render has finished!\n Logs for this render can be found in this folder: \"BlenderBatch\\tasks\\" + taskName + "\\logs\"\n\n Press enter to continue";
	std::getchar();
}