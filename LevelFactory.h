#pragma once
#include "Level.h"
class LevelFactory
{
public:
	LevelFactory();
	virtual ~LevelFactory();

public:
	static void randomizeTheLevel();
	static void Retry();
	static std::shared_ptr<Level> getCurrentLevel();
	static void fillTheLevels();
	static void throwEnemy();

public:
	static short currentLevel;
	static std::map<short, std::shared_ptr<Level>> listOfLevels;
};

