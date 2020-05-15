#include "pch.h"
#include "StringHelpers.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"
#include "Ladder.h"
#include "Block.h"
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(60);
	// Draw Statistic Font
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Donkey Kong ESGI 2020");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(20);
	music.playMusic();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();

		if (gameStatus != Status::End) 
			watchMario();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
	{
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::Down)
	{
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::Left)
	{
		mIsMovingLeft = isPressed;
		music.triggerWalkSound(isPressed);
	}
	else if (key == sf::Keyboard::Right)
	{
		mIsMovingRight = isPressed;
		music.triggerWalkSound(isPressed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && levelFactory.getCurrentLevel()->mPlayer->cptFall == 10)
	{
		mWindow.setKeyRepeatEnabled(false);
		if(levelFactory.getCurrentLevel()->mPlayer->cptFall == 10)
		{
			levelFactory.getCurrentLevel()->mPlayer->mIsJumping = true;
			music.triggerJumdSound();
		}	
	} 
	else if (key == sf::Keyboard::Return)
	{
		mEnterIsPressed = isPressed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		music.nextMusic();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		music.resumePauseMusic();
	}
}

void Game::update(sf::Time elapsedTime)
{
	switch(gameStatus)
	{
	case Status::Running:
		if (mIsMovingUp)
		{
			levelFactory.getCurrentLevel()->mPlayer->GoUp(elapsedTime);
		}	
		if (mIsMovingDown)
		{
			levelFactory.getCurrentLevel()->mPlayer->GoDown(elapsedTime);
		}	
		if (mIsMovingLeft)
		{
			levelFactory.getCurrentLevel()->mPlayer->GoLeft(elapsedTime);
		}	
		if (mIsMovingRight)
		{
			levelFactory.getCurrentLevel()->mPlayer->GoRight(elapsedTime);
		}	
		if (levelFactory.getCurrentLevel()->mPlayer->mIsJumping)
		{
			levelFactory.getCurrentLevel()->mPlayer->Jump(elapsedTime);
		}
		if (!mIsMovingUp && !mIsMovingDown && !mIsMovingLeft && !mIsMovingRight && !levelFactory.getCurrentLevel()->mPlayer->mIsJumping)
		{
			levelFactory.getCurrentLevel()->mPlayer->stopMoving();
		}
		for (std::shared_ptr<Enemy> enemy : levelFactory.getCurrentLevel()->mEnemies)
		{
            enemy->Move(elapsedTime);
		}
		timeoutDonkeyMovement(1000000000);

		break;
	case Status::End:
	    mEndGameText.setString("Game over");
		levelFactory.Retry();
		music.playMusic();		
		gameStatus = Status::Running;
		break;
	}
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : levelFactory.getCurrentLevel()->mBlocks)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mBody);
	}

	for (std::shared_ptr<Entity> entity : levelFactory.getCurrentLevel()->mLadders)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mBody);
	}

	for (std::shared_ptr<Entity> entity : levelFactory.getCurrentLevel()->mEnemies)
	{
		mWindow.draw(entity->mBody);
	}

	mWindow.draw(levelFactory.getCurrentLevel()->mPeach->mBody);
	mWindow.draw(levelFactory.getCurrentLevel()->donkey->mBody);
	mWindow.draw(levelFactory.getCurrentLevel()->mPlayer->mBody);

	mWindow.draw(mStatisticsText);
	mWindow.draw(mEndGameText);

	mWindow.display();
}

void Game::timeoutDonkeyMovement(int x)
{	

	if(levelFactory.getCurrentLevel()->donkey->currentAnimation > 50 && levelFactory.getCurrentLevel()->donkey->currentAnimation < 100)
	{	
		levelFactory.getCurrentLevel()->donkey->updateTextureToRightDirection();
		incrementDokeyFrame();
	}
	else if (levelFactory.getCurrentLevel()->donkey->currentAnimation > 100 && levelFactory.getCurrentLevel()->donkey->currentAnimation < 150)
	{
		levelFactory.getCurrentLevel()->donkey->updateTextureToLeftDirection();
		incrementDokeyFrame();
	}
	else if (levelFactory.getCurrentLevel()->donkey->currentAnimation > 150 && levelFactory.getCurrentLevel()->donkey->currentAnimation < 200)
	{
		levelFactory.getCurrentLevel()->donkey->updateTextureToRightDirection();
		incrementDokeyFrame();
	}
	else if (levelFactory.getCurrentLevel()->donkey->currentAnimation > 200 && levelFactory.getCurrentLevel()->donkey->currentAnimation < 250)
	{
		levelFactory.getCurrentLevel()->donkey->updateTextureToLeftDirection();
		incrementDokeyFrame();
	}
	else if(levelFactory.getCurrentLevel()->donkey->currentAnimation > 250)
	{
		levelFactory.getCurrentLevel()->donkey->updateTextureToFixedStatut();
		levelFactory.getCurrentLevel()->donkey->resetAnimationFrame();
		levelFactory.throwEnemy();
	}
	else
	{
        incrementDokeyFrame();
	}

}
void Game::incrementDokeyFrame()
{
	levelFactory.getCurrentLevel()->donkey->setAnimationFrame(levelFactory.getCurrentLevel()->donkey->currentAnimation + 1);
}
void Game::timeoutGame(int x, short gameState)
{
  for (int i=2; i<x; ++i);
  gameOver(gameState);
  music.resumePauseMusic();
}

void Game::watchMario()
{
	std::shared_ptr<Player> mario = levelFactory.getCurrentLevel()->mPlayer;
	
	if ((mario->notTouchingFloor() && !mario->mIsJumping && mario->cptFly == 0) || (mario->IsOnLadder() && !mario->mIsJumping && mario->cptFall != 10))
		mario->GoDown(sf::microseconds(10000));
	if (mario->isTouchingEnemy() || mario->isOutOfPlayZone())
	{	
		music.DieSound();
		mStatisticsText.setString(
			"Game over !"
		);
		mWindow.draw(mStatisticsText);
		mWindow.display();
		timeoutGame(1500020007, 0); 
	}
	if (mario->isTouchingPeach())
	{   
		mStatisticsText.setString(
			"Winner winner chiken dinner !!"
		);
		mWindow.draw(mStatisticsText);
		mWindow.display();
		music.WinSound();
		timeoutGame(750020007, 1);
	}
	mario->GravityHandle();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "  |  " +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us\n"+
			"Press A to play the next music" +"\n"+
			"To stop music press Z" + "\n"
		);

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}


	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{

	}
}

void Game::gameOver(short state)
{
	gameStatus = Status::End;
	if (state == 0)
	{
		mEndGameText.setString("Your dead !\n Wann replay?");
	}
	else
	{
		levelFactory.getCurrentLevel()->gameWon = true;
		levelFactory.getCurrentLevel()->donkey->resetAnimationFrame();	
	}
}
