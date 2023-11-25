#include <iostream>
#include "Global.hpp"
#include "Files.hpp"
#include "Draw.hpp"
#include "MainMenu.hpp"

int main()
{
	HWND hwnd = GetConsoleWindow();
	SetWindowTextW(hwnd, StringToWide("BlenderBatch " + VERSION).c_str());

	RefreshScreen();

	CreateFolder("BlenderBatch");
	CreateFolder("BlenderBatch\\config");
	CreateFolder("BlenderBatch\\tasks");

	if (!CheckFile("BlenderBatch\\config\\blenderPath"))
	{
		std::cout << " Blender Path:\n";
		DrawCursor();
		std::string blenderPath = "";
		getline(std::cin, blenderPath);

		blenderPath = RemoveCharacter(blenderPath, '"');
		WriteFile("BlenderBatch\\config\\blenderPath", blenderPath);
	}

	InitMainMenu();

	return 0;
}