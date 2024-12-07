#pragma once
#include <string>
#include <fstream>

class Utils
{
public:
	static void initLog(int argc, char** argv);
	static void switchInit();
	static std::ifstream loadFile(std::string path);
	static std::ifstream loadFile(std::string path, std::ios_base::openmode mode);

protected:
};