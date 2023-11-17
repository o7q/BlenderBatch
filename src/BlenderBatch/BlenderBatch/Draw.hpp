#pragma once

#include <iostream>
#include <conio.h>
#include "Global.hpp"

using namespace std;

void DrawCursor()
{
	cout << " -> ";
}

void RefreshScreen()
{
	system("cls");
	cout << "  ___ _             _         ___       _      _    \n"
			" | _ ) |___ _ _  __| |___ _ _| _ ) __ _| |_ __| |_  \n"
			" | _ \\ / -_) ' \\/ _` / -_) '_| _ \\/ _` |  _/ _| ' \\ " << VERSION << "\n"
			" |___/_\\___|_||_\\__,_\\___|_| |___/\\__,_|\\__\\__|_||_| by o7q\n\n";
}