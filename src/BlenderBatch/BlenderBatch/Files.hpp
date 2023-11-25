#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "Strings.hpp"

namespace fs = std::filesystem;

void CreateFolder(std::string folderPath);
void RemoveFolder(std::string folderPath);
std::string ReadFile(std::string file);
bool CheckFile(std::string file);


void CreateFolder(std::string folderPath)
{
	if (!fs::exists(folderPath))
		fs::create_directory(folderPath);
}

void RemoveFolder(std::string folderPath)
{
	try
	{
		if (fs::exists(folderPath)) {
			// remove the directory and subdirectories
			fs::remove_all(folderPath);
			std::cout << "Folder and its contents deleted successfully." << std::endl;
		}
		else
			std::cout << "Folder does not exist." << std::endl;
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << "Error deleting folder: " << e.what() << std::endl;
	}
}

void WriteFile(std::string file, std::string content)
{
	std::ofstream f;
	f.open(file);
	f << content;
	f.close();
}

std::string ReadFile(std::string file)
{
	if (!CheckFile(file))
		return "";
	std::stringstream f;
	f << std::ifstream(file).rdbuf();
	return f.str();
}

bool CheckFile(std::string file)
{
	std::ifstream f;
	f.open(file);
	if (f)
		return true;
	return false;
}