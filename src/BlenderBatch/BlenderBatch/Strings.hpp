#pragma once

#include <iostream>
#include <algorithm>

using namespace std;

wstring StringToWide(string input);
string RemoveCharacter(string input, char inputChar);

wstring StringToWide(string input)
{
    wstring wInput(input.begin(), input.end());
    return wInput;
}

string RemoveCharacter(string input, char inputChar)
{
    input.erase(std::remove(input.begin(), input.end(), inputChar), input.end());
    return input;
}