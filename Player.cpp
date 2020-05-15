#include "pch.h"
#include "Player.h"
#include "LevelFactory.h"


const int JUMPING_FRAMES = 10;
const int FLYING_FRAMES = 20;


Player::~Player() {}
Player::Player(float x, float y) : Entity(x, y)
{
	m_speed = 150.f;
	updateTexture("Media/Textures/mario_right_side.png");
	mBody.setPosition(x, y);
}

void Player::Jump(sf::Time elapsedTime)
{
	if (!this->IsOnLadder())
	 {
		GoesToTheRight ? updateTexture(mario_jumping_right) : updateTexture(mario_jumping_left);
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= m_speed;
		this->mBody.move(movement * elapsedTime.asSeconds());
	}
}

void Player::GravityHandle() {
	if (mIsFlying()) {
		updateFlyingTexture();
	}
	if (cptFly > 0 && cptFly < FLYING_FRAMES) {
		cptFly++;
	}
	else {
		if (cptJump == JUMPING_FRAMES) {
			cptFly++;
			mIsJumping = false;
		}
		if (!mIsJumping)
		{
			cptJump = 0;
			if (cptFly == FLYING_FRAMES)
			{
				cptFly = 0;	
			}
		}
		else
		{
			cptJump++;
			cptFall--;
		}
		if (!mIsJumping && cptFall != JUMPING_FRAMES)
		{
			cptFall++;
		}
	}
}
void Player::updateTextureDirection() {
	if(!IsAboveOrOnLadder())
	{
		GoesToTheRight ? updateTexture(mario_moving_right) : updateTexture(mario_moving_left);
	}
}
void Player::GoLeft(sf::Time elapsedTime)
{
	if (cptFall == JUMPING_FRAMES) {
		updateTextureDirection();
	}
	Entity::GoLeft(elapsedTime);
}

void Player::GoRight(sf::Time elapsedTime)
{
	if (cptFall == JUMPING_FRAMES) {
		updateTextureDirection();
	}
	Entity::GoRight(elapsedTime);
}

bool Player::GoUp(sf::Time elapsedTime)
{
	if(IsAboveOrOnLadder())
		updateTexture(mario_moving_up);
	return Entity::GoUp(elapsedTime); 
}

bool Player::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder() || notTouchingFloor())
	{
		if (IsOnLadder()) 
			updateTexture(mario_moving_up);

		sf::Vector2f movement(0.f, 0.f);
		movement.y += m_speed;
		this->mBody.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}
void Player::updateFlyingTexture()
{
	GoesToTheRight ? updateTexture(mario_jumping_right) : updateTexture(mario_jumping_left);
}
bool Player::mIsFlying()
{
	return cptFall != JUMPING_FRAMES;
}
void Player::stopMoving()
{

	if (!this->IsAboveOrOnLadder())
	{
		if (GoesToTheRight)
		{
			updateTexture(mario_right_side);
		}
		else
		{
			updateTexture(mario_left_side);
		}
	}

}

bool Player::isTouchingEnemy()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::getCurrentLevel()->mEnemies)
	{
		sf::FloatRect marioDimensions = entity->mBody.getGlobalBounds();
		marioDimensions.top += 10;
		if (this->mBody.getGlobalBounds().intersects(marioDimensions))
		{
			// std::cout<<"touching enemy"<<"\n";
			return true;
		}
	}
	return false;
}


bool Player::isTouchingPeach()
{
    std::shared_ptr<Entity> mPeach = LevelFactory::getCurrentLevel()->mPeach;
	sf::FloatRect peachDimensions = mPeach->mBody.getGlobalBounds();
	if (this->mBody.getGlobalBounds().intersects(peachDimensions))
	{
		return true;
	}
	return false;
}



