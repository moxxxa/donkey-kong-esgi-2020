#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(float x, float y) : Entity(x, y)
{
	m_speed = 100.f;
	updateTexture(goombaRightFoot);
	mBody.setPosition(x, y);
    // std::cout<<"enemy position pushed"<<"\n";
}

Enemy::~Enemy()
{
}

void Enemy::Move(sf::Time elapsedTime)
{	
	
	if (goombaUp)
	{
		if (!GoUp(elapsedTime))
		{
			upDownFramer = rand() % (500 - 20) + 20;
			goombaUp = false;
		}
	}
	else if (goombaDown)
	{
		if (!GoDown(elapsedTime))
		{
			upDownFramer = rand() % (500 - 20) + 20;
			goombaDown = false;
		}
	}
	else
	{	
		if (upDownFramer != 0)
		{
			upDownFramer -= 1;
			changeDirection(elapsedTime);
		}
		else
		{
			if (GoDown(elapsedTime))
			{
				goombaDown = true;
			}
			else if (GoUp(elapsedTime))
			{
				goombaUp = true;
			}
			else
			{
				changeDirection(elapsedTime);
			}
		}
	}
	
}

void Enemy::changeDirection(sf::Time elapsedTime)
{
	countWalks ++;
	if (countWalks < 10)
	{
		updateTexture(goombaRightFoot);
	}
	else
	{
		updateTexture(goombaLeftFoot);
	}
	if (countWalks > 20)
	{
		countWalks = 0;
	}	
	reverseSideOnceUponEdge(elapsedTime);
	if (GoesToTheRight)
	{
		Entity::GoRight(elapsedTime);
	}
	else
	{
		Entity::GoLeft(elapsedTime);
	}
}

void Enemy::reverseSideOnceUponEdge(sf::Time elapsedTime)
{	
	if (notTouchingFloor())
	{
		if (Enemy::GoesToTheRight)
			Entity::GoLeft(elapsedTime);
		else
			Entity::GoRight(elapsedTime);
	}
	
}
