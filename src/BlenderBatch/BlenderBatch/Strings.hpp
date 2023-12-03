#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

std::wstring StringToWide(const std::string& input);
std::string RemoveCharacter(std::string input, const char& inputChar);
bool IsInteger(const std::string& input);
std::vector<std::string> SplitString(const std::string& input);

std::wstring StringToWide(const std::string& input)
{
    std::wstring wInput(input.begin(), input.end());
    return wInput;
}

std::string RemoveCharacter(std::string input, const char& inputChar)
{
    input.erase(remove(input.begin(), input.end(), inputChar), input.end());
    return input;
}


bool IsInteger(const std::string& input)
{
    try
    {
        std::stoi(input); // try to convert the string to an integer
        return true;
    }
    catch (...)
    {
        return false;
    }
}

std::vector<std::string> SplitString(const std::string& input, char splitCharacter)
{
    std::vector<std::string> result;
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, splitCharacter))
    {
        result.push_back(token);
    }

    return result;
}