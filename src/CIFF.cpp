#include "CIFF.h"
#include <loguru.hpp>
#include "Utils.h"
#include <fstream>

//static because shoud only be one ciff structure per game
//optionally patched by the promotree or loose chunks
/*CIFF::CIFF()
{
}*/

bool CIFF::Load_Tree(char* filename)
{
	std::ifstream inFile = Utils::loadFile(filename);

	if (inFile.fail()) {
		LOG_F(ERROR, "Could not open CIFF file: %s", filename);
		inFile.close();
		return false;
	}
	//fh.read((char*)&h.id, sizeof(h.id));
	//padding issues:
	//https://stackoverflow.com/questions/43547040/reading-a-struct-in-binary-with-ifstream-read

	inFile.close();
	return true;
}