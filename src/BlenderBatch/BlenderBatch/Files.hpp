#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "Strings.hpp"

using namespace std;

void CreateFolder(string directory);
void WriteFile(string file, string content);
string ReadFile(string file);
bool CheckFile(string file);

void CreateFolder(string directory)
{
    wstring wDirectory = StringToWide(directory);
    CreateDirectory(wDirectory.c_str(), nullptr);
}

void WriteFile(string file, string content)
{
    ofstream f;
    f.open(file);
    f << content;
    f.close();
}

string ReadFile(string file)
{
    if (!CheckFile(file))
        return "";
    stringstream f;
    f << ifstream(file).rdbuf();
    return f.str();
}

bool CheckFile(string file)
{
    ifstream f;
    f.open(file);
    if (f)
        return true;
    return false;
}