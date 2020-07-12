#pragma once
#include "pch.h"
#include "Entity.h"
#include <SFML/Audio.hpp>

class Player : public Entity
{
public:
	Player(float x, float y);
	virtual ~Player();
	

public:
	void updateTextureDirection();
	bool GoDown(sf::Time elapsedTime);
	void GoLeft(sf::Time elapsedTime) override; 
	void GoRight(sf::Time elapsedTime) override; 
	bool GoUp(sf::Time elapsedTime) override;
	void Jump(sf::Time elapsedTime);
	void stopMoving();
	bool mIsFlying();
	void updateFlyingTexture();
	void GravityHandle();
	bool isTouchingEnemy();
	bool isTouchingPeach();

public:
	bool mIsJumping = false;
	int cptJump = 0;
	int cptFall = 10;
	int cptFly = 0;

public: 
	sf::SoundBuffer mDiesBuffer; 
	sf::SoundBuffer mWinsBuffer;
	sf::Sound mDeathSound; 
	sf::Sound mWin1Sound;

public:

	std::string mario_right_side = "Media/Textures/mario_right_side.png";
	std::string mario_moving_right = "Media/Textures/mario_moving_right.png";
	std::string mario_jumping_right = "Media/Textures/mario_jumping_right.png";
	std::string mario_left_side = "Media/Textures/mario_left_side.png";
	std::string mario_moving_left = "Media/Textures/mario_moving_left.png";
	std::string mario_jumping_left = "Media/Textures/mario_jumping_left.png";
	std::string mario_moving_up = "Media/Textures/mario_escalating.png";
	std::string mDeathSoundPath = "Media/Sounds/death.wav"; 
	std::string mWin1SoundPath = "Media/Sounds/win1.wav";
};

