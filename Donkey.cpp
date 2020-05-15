#include "pch.h"
#include "Donkey.h"


Donkey::~Donkey() {}

Donkey::Donkey(float x, float y)
{
	updateTexture(donkey);
	mBody.setPosition(x, y);
}


void Donkey::updateTextureToRightDirection()
{
    updateTexture(donkey_right_side);
}

void Donkey::updateTextureToLeftDirection()
{
    updateTexture(donkey_left_side);
}

void Donkey::updateTextureToFixedStatut()
{
    updateTexture(donkey);
}

void Donkey::setAnimationFrame(int value)
{
    currentAnimation = value;
}

void Donkey::resetAnimationFrame()
{
    currentAnimation = 0;
}

void Donkey::updateTexture(std::string path)
{
	mTexture.loadFromFile(path);
	mBody.setTexture(mTexture);
}

void Donkey::setNumberOfPushedEnemys(int value)
{
    cptEnemy = value;
}



