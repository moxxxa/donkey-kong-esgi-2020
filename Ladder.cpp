#include "pch.h"
#include "Ladder.h"


Ladder::Ladder()
{
}

Ladder::Ladder(float x, float y) : Entity(x, y)
{	
	mTexture.loadFromFile("Media/Textures/Echelle.png");
	mBody.setTexture(mTexture);
	mBody.setPosition(x, y);
}


Ladder::~Ladder()
{
}
