#pragma once

#define BLOCK_SPACE 110.f
#define COIN_SPACE 120.f
#define ENEMY_COUNT 4
#include "LevelFactory.h"
#include "Music.h"

enum Status
{
	Running,
	End
};

class Game
{
public:
	Game();
	virtual ~Game(){};


public:
	void run();
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();
	void watchMario();
	void updateStatistics(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void gameOver(short state);
	void timeoutDonkeyMovement(int x);
	void timeoutGame(int x, short gameState);
	void incrementDokeyFrame();

public:
	static const sf::Time	TimePerFrame;
	Status 			gameStatus = Status::Running;
	LevelFactory	levelFactory;
	Music 			music;

	sf::RenderWindow		mWindow;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	sf::Text				mEndGameText;
	sf::Sprite				mPeach;
	sf::Texture 			mPeachTexture;

	std::size_t	mStatisticsNumFrames;

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	bool mEnterIsPressed;
	
};
