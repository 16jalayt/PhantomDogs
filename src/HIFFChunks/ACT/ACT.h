#pragma once
#include <fstream>

class ACT
{
public:
	static bool Parse(std::ifstream& inFile, int chunkLen, int chunkStart);
protected:
};
