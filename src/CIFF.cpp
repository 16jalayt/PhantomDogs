#include "CIFF.h"
//gives linker error
//#include <loguru.hpp>
#include "Engine/Utils.h"
#include <fstream>

//static because shoud only be one ciff structure per game
//optionally patched by the promotree or loose chunks
/*CIFF::CIFF()
{
}*/

//TODO: load tree
bool CIFF::Load_Tree(std::string filename)
{
	std::ifstream inFile = std::ifstream(PathFixer(filename), std::ios::in | std::ios::binary | std::ios::ate);

	if (inFile.fail()) {
		LOG_F(ERROR, "Could not open CIFF file: %s", filename.c_str());
		inFile.close();
		return false;
	}
	//fh.read((char*)&h.id, sizeof(h.id));
	//padding issues:
	//https://stackoverflow.com/questions/43547040/reading-a-struct-in-binary-with-ifstream-read

	inFile.close();
	return true;
}