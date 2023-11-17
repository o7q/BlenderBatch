#include <iostream>
#include <string>
#include <Windows.h>
#include "Global.hpp"
#include "Files.hpp"
#include "Draw.hpp"

using namespace std;

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
        cout << " Blender Path:\n";
        DrawCursor();
        string blenderPath = "";
        getline(cin, blenderPath);

        blenderPath = RemoveCharacter(blenderPath, '"');
        WriteFile("BlenderBatch\\config\\blenderPath", blenderPath);
    }

    //while (true)
    //{
    //    RefreshScreen();

    //    cout << " Select a render job by typing its name\n - Create one by typing !<JOBNAME>\n - Delete one by typing @<JOBNAME>\n - Type # to exit\n\n";


    //}

	return 0;
}