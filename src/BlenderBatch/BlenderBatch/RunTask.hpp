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
	std::string queue = task + "\\_queue";

	try {
		if (fs::exists(queue) && fs::is_directory(queue)) {
			// iterate over the contents of the directory
			for (const auto& entry : fs::directory_iterator(queue)) {
				// check if the entry is a regular file
				if (fs::is_regular_file(entry.path())) {
					tasks.push_back(entry.path().string());
				}
			}
		}
		else {
			std::cout << "Directory does not exist or is not a valid directory." << std::endl;
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Error loading subtasks: " << e.what() << std::endl;
	}

	for (int i = 0; i < tasks.size(); i++)
	{
		QueueConfig queue;

		std::string subtaskString = ReadFile(tasks[i]);
		std::vector subtask = SplitString(subtaskString, '\n');

		for (int j = 0; j < subtask.size(); j++)
		{
			std::vector subtaskSplit = SplitString(subtask[j], '¶');
			if (subtaskSplit[0] == "BLEND_FILE") queue.BLEND_FILE = subtaskSplit[1];
			if (subtaskSplit[0] == "RENDER_ENGINE") queue.RENDER_ENGINE = subtaskSplit[1];
			if (subtaskSplit[0] == "RENDER_MODE") queue.RENDER_MODE = subtaskSplit[1];
			if (subtaskSplit[0] == "START_FRAME") queue.START_FRAME = subtaskSplit[1];
			if (subtaskSplit[0] == "END_FRAME") queue.END_FRAME = subtaskSplit[1];
		}

		std::string renderScript = "";
		std::string engineScript = "";
		if (queue.RENDER_ENGINE != "__PROJECT__")
			engineScript = "-E " + queue.RENDER_ENGINE + " ";

		if (queue.RENDER_MODE == "__ANIMATION__")
			renderScript = "powershell -command \"\"" + blenderPath + "\" -b '" + queue.BLEND_FILE + "' " + engineScript + "-s " + queue.START_FRAME + " -e " + queue.END_FRAME + " -a /e | tee-object '" + task + "\\logs\\" + std::to_string(i) + ".log'\"";
		else
			renderScript = "powershell -command \"\"" + blenderPath + "\" -b '" + queue.BLEND_FILE + "' " + engineScript + "-f " + queue.START_FRAME + " /e | tee-object '" + task + "\\logs\\" + std::to_string(i) + ".log'\"";

		system(renderScript.c_str());
	}

	std::cout << "\n\n The render has finished!\n Logs for this render can be found in this folder: \"BlenderBatch\\tasks\\" + taskName + "\\logs\"\n\n Press enter to continue";
	std::getchar();
}