#include "pch.h"
#include "Block.h"


Block::Block()
{
}

Block::Block(float x, float y) : Entity(x, y)
{
	mTexture.loadFromFile("Media/Textures/Block.png");
	mBody.setTexture(mTexture);
	mBody.setPosition(x, y);
}


Block::~Block()
{
}
