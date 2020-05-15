#include "pch.h"
#include "LevelFactory.h"
#include <time.h>

std::map<short, std::shared_ptr<Level>> LevelFactory::listOfLevels;
short LevelFactory::currentLevel;

LevelFactory::LevelFactory()
{
	randomizeTheLevel();
	fillTheLevels();
}

LevelFactory::~LevelFactory(){}

void LevelFactory::randomizeTheLevel()
{
	srand (time(NULL));
	currentLevel = rand() % 2 + 1;
}

void LevelFactory::Retry()
{
	randomizeTheLevel();
	listOfLevels.clear();
	fillTheLevels();
}

std::shared_ptr<Level> LevelFactory::getCurrentLevel()
{
	return listOfLevels.at(currentLevel);
}

void LevelFactory::fillTheLevels()
{
	// LEVEL 1
	std::shared_ptr<Level> level1 = std::make_shared<Level>();
	
	listOfLevels.insert(std::pair<int, std::shared_ptr<Level>>(1, level1));

	level1->mPeach = std::make_shared<Entity>(600.f, 55.f, "Media/Textures/peach.png");

	level1->donkey = std::make_shared<Donkey>(350.f, 70.f);
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!(j == 1 && (i == 1 || i == 2)))
			{
				std::shared_ptr<Block> se = std::make_shared<Block>(100.f + 70.f * (i + 1.f), 110.f * (j + 1.f));
				level1->mBlocks.push_back(se);
			} 
		}
	}

	std::pair<float, float> laddersPositions[5]{ std::make_pair(410.f, 473.f), std::make_pair(190.f, 363.f), std::make_pair(590.f, 253.f), std::make_pair(190.f, 143.f), std::make_pair(650.f, 143.f) };
	for (const std::pair<float, float> ladderPosition : laddersPositions)
	{
		std::shared_ptr<Ladder> ladder = std::make_shared<Ladder>(ladderPosition.first, ladderPosition.second);
		level1->mLadders.push_back(ladder);
	}

	level1->mPlayer = std::make_shared<Player>(170.f, 470.f);


	// LEVEL 2
	
	std::shared_ptr<Level> level2 = std::make_shared<Level>();
	
	listOfLevels.insert(std::pair<int, std::shared_ptr<Level>>(2, level2));

	level2->mPeach = std::make_shared<Entity>(600.f, 55.f, "Media/Textures/peach.png");

	level2->donkey = std::make_shared<Donkey>(350.f, 65.f);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::shared_ptr<Block> se = std::make_shared<Block>(100.f + 70.f * (i + 1.f), 110.f * (j + 1.f));
			level2->mBlocks.push_back(se);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Ladder> se = std::make_shared<Ladder>(100.f + 80.f * (i + 3), 110.f * (i + 1) + 33);
		level2->mLadders.push_back(se);
	}

	level2->mPlayer = std::make_shared<Player>(170.f, 480);

}	

void LevelFactory::throwEnemy()
{
	if (getCurrentLevel()->donkey->cptEnemy < getCurrentLevel()->donkey->max_enemy)
	{
		// push new enmey
		std::shared_ptr<Enemy> se = std::make_shared<Enemy>(650.f, 80.f);
		getCurrentLevel()->mEnemies.push_back(se);
		getCurrentLevel()->donkey->setNumberOfPushedEnemys(getCurrentLevel()->donkey->cptEnemy + 1);
	}
}
