#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Strings.hpp"

namespace fs = std::filesystem;

void CreateFolder(const std::string& folderPath);
void RemoveFolder(const std::string& folderPath);
std::string ReadFile(const std::string& file);
bool CheckFile(const std::string& file);


void CreateFolder(const std::string& folderPath)
{
	if (!fs::exists(folderPath))
		fs::create_directory(folderPath);
}

void RemoveFolder(const std::string& folderPath)
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

void WriteFile(const std::string& file, const std::string& content)
{
	std::ofstream f;
	f.open(file);
	f << content;
	f.close();
}

std::string ReadFile(const std::string& file)
{
	if (!CheckFile(file))
		return "";
	std::stringstream f;
	f << std::ifstream(file).rdbuf();
	return f.str();
}

bool CheckFile(const std::string& file)
{
	std::ifstream f;
	f.open(file);
	if (f)
		return true;
	return false;
}