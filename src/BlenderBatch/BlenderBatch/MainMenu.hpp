#include <iostream>
#include <vector>
#include <string>
#include "Windows.h"
#include "Draw.hpp"
#include "Strings.hpp"
#include "CreateTask.hpp"
#include "RunTask.hpp"

void InitMainMenu();

void InitMainMenu()
{
	std::string blenderPath = ReadFile("BlenderBatch\\config\\blenderPath");

	while (true)
	{
		RefreshScreen();

		std::cout << " Select a render job by typing its number\n - Create one by typing !<JOB_NAME>\n - Delete one by typing @<JOB_NUMBER>\n - Type # to exit\n\n";

		#pragma region ListTasks

		int index = 1;
		std::vector<std::string> tasks;

		try
		{
			if (fs::exists("BlenderBatch\\tasks") && fs::is_directory("BlenderBatch\\tasks"))
			{
				// iterate over the contents of the directory
				for (const auto& entry : fs::directory_iterator("BlenderBatch\\tasks"))
				{
					// check if the entry is a directory
					if (fs::is_directory(entry.path()))
					{
						std::cout << "[" << index << "] " << entry.path().filename() << std::endl;
						tasks.push_back(entry.path().filename().string());
						index++;
					}
				}
			}
			else
				std::cout << "Directory does not exist or is not a valid directory." << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cerr << "Error listing tasks: " << e.what() << std::endl;
		}

		#pragma endregion

		DrawCursor();

		std::string select = "";
		getline(std::cin, select);

		if (select[0] == '!')
			CreateTask(select.substr(1), blenderPath);
		else if (select[0] == '@' && IsInteger(select.substr(1)))
		{
			int selectInt = std::stoi(select.substr(1));
			if (selectInt > 0 && selectInt - 1 < tasks.size())
				RemoveFolder("BlenderBatch\\tasks\\" + tasks[selectInt - 1]);
		}
		else if (select[0] == '#')
			return;
		else if (IsInteger(select))
		{
			int selectInt = std::stoi(select);
			if (selectInt > 0 && selectInt - 1 < tasks.size())
				StartRenderTask(tasks[selectInt - 1], blenderPath);
		}
	}
}