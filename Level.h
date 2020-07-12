#pragma once
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Ladder.h"
#include "Block.h"
#include "Donkey.h"


class Level
{
public:
	Level();
	virtual ~Level();

public:
	bool gameWon = false;
	std::shared_ptr<Entity> mPeach;
	std::shared_ptr<Donkey> donkey;
	std::shared_ptr<Player> mPlayer;
	std::vector<std::shared_ptr<Enemy>> mEnemies;
	std::vector<std::shared_ptr<Block>> mBlocks;
	std::vector<std::shared_ptr<Ladder>> mLadders;
};

