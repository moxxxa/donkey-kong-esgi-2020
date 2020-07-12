#pragma once


class Entity
{
public:
	Entity();
	Entity(float x, float y);
	Entity(float x, float y, std::string pathToPNG);
	virtual ~Entity() {};

public:
	virtual void GoRight(sf::Time elapsedTime);
	virtual bool GoUp(sf::Time elapsedTime);
	virtual void GoLeft(sf::Time elapsedTime);
	virtual void updateTexture(std::string path);
	bool GoDown(sf::Time elapsedTime);
	bool IsOnLadder();		
	bool IsAboveOrOnLadder();
	bool hitBlocks();
	bool notTouchingFloor();
	bool isOutOfPlayZone();

public:
	bool GoesToTheRight = true;
	sf::Sprite mBody;
	bool mEnabled = true;
	sf::Texture mTexture;
	float	m_speed;
};