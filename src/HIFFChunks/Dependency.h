#include "Engine/Globals.h"
#include <loguru.hpp>
#include <vector>
#include <fstream>
#include <Engine/Utils.h>
#include "../Scene.h"

typedef struct Dependency
{
	int depType;
	int label;
	bool condition;
	int operatorType;
	Scaled_Rect time;
} Dependency;

std::vector<Dependency> parseDeps(std::ifstream& inFile, int chunkLen, int chunkStart)
{
	std::vector<Dependency> deps;
	//if not last byte in chunk
	while ((chunkStart + chunkLen + 8) != (int)inFile.tellg())
	{
		Dependency dep{};
		dep.depType = readShort(inFile);
		dep.label = readShort(inFile);
		dep.condition = readShort(inFile);
		dep.operatorType = readShort(inFile);
		dep.time = { readShort(inFile), readShort(inFile), readShort(inFile), readShort(inFile) };
		deps.push_back(dep);
		LOG_F(INFO, "    --Dep DepType:%d Label:%d Cond:%d  Bool:%d", dep.depType, dep.label, dep.condition, dep.operatorType);
	}
	return deps;
}

bool checkDeps(std::vector<Dependency> deps)
{
	if (deps.size() == 0)
		return true;
	for (const Dependency dep : deps)
	{
		//TODO: other types
		//DT_EVENT
		if (dep.depType == 2)
		{
			//if should or
			if (dep.operatorType)
			{
				//TODO: figure out or. All dependencies?
				if (flags[dep.label - 1000] || dep.condition)
					continue;
				else
					return false;
			}
			//and
			else
			{
				if (flags[dep.label - 1000] == dep.condition)
					continue;
				else
					return false;
			}
		}
		//TODO: broken
		//DT_SCENE_COUNT
		if (dep.depType == 9)
		{
			//if should or
			if (dep.operatorType)
			{
				return true;
			}
			//and
			else
			{
				return false;
			}
		}
	}

	return true;
}