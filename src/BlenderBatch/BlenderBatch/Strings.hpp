#pragma once

#include <algorithm>

std::wstring StringToWide(std::string input);
std::string RemoveCharacter(std::string input, char inputChar);

std::wstring StringToWide(std::string input)
{
    std::wstring wInput(input.begin(), input.end());
    return wInput;
}

std::string RemoveCharacter(std::string input, char inputChar)
{
    input.erase(remove(input.begin(), input.end(), inputChar), input.end());
    return input;
}