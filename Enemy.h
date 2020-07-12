#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(float x, float y);
	virtual ~Enemy();

public:
	void Move(sf::Time elapsedTime);

private:
	void changeDirection(sf::Time elapsedTime);
	void reverseSideOnceUponEdge(sf::Time elapsedTime);

private:
	bool goombaUp = false;
	bool goombaDown = false;
	int upDownFramer = 0;
	int countWalks = 0;

protected: 
	std::string goombaLeftFoot = "Media/Textures/goomba-left-foot.png"; 
	std::string goombaRightFoot = "Media/Textures/goomba-right-foot.png";
};

