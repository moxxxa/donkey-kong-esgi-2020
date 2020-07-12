#pragma once
#include "pch.h"

class Donkey
{
public:
	Donkey(float x, float y);
	virtual ~Donkey();
	

public:
	void updateTextureToRightDirection();
	void updateTextureToLeftDirection();
	void updateTextureToFixedStatut();
	void updateTexture(std::string path);
	void setAnimationFrame(int value);
	void resetAnimationFrame();
	void setNumberOfPushedEnemys(int value);

public:
	int currentAnimation = 0;
	int cptEnemy = 0;
    sf::Sprite mBody;
	sf::Texture mTexture;
	int max_enemy = 5;


public:
    std::string donkey = "Media/Textures/donkey-not-mooving.png";
	std::string donkey_right_side = "Media/Textures/donkey-right.png";
	std::string donkey_left_side = "Media/Textures/donkey-left.png";
};

