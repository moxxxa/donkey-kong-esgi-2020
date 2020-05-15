#include "pch.h"
#include "LevelFactory.h"
#include "Entity.h"

Entity::Entity(){}

Entity::Entity(float x, float y){}

Entity::Entity(float x, float y, std::string pathToPNG)
{
	mBody.setPosition(x, y);
	mTexture.loadFromFile(pathToPNG);
	mBody.setTexture(mTexture);
}

void Entity::GoRight(sf::Time elapsedTime)
{
	if (!hitBlocks())
	{
		GoesToTheRight = true;
		sf::Vector2f movement(0.f, 0.f);
		movement.x += m_speed;
		this->mBody.move(movement * elapsedTime.asSeconds());
	}
}

void Entity::GoLeft(sf::Time elapsedTime)
{
	if (!hitBlocks())
	{
		GoesToTheRight = false;
		sf::Vector2f movement(0.f, 0.f);
		movement.x -= m_speed;
		this->mBody.move(movement * elapsedTime.asSeconds());
	}
}

bool Entity::GoUp(sf::Time elapsedTime)
{
	if (this->IsOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= m_speed;
		this->mBody.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

bool Entity::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y += m_speed;
		this->mBody.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

bool Entity::IsOnLadder()
{
	
	for (std::shared_ptr<Entity> entity : LevelFactory::getCurrentLevel()->mLadders)
	{
		sf::FloatRect fr = entity->mBody.getGlobalBounds();
		// we add the height of the block texture so our entity can hike on it
		fr.top -= 33;
		fr.height += 33;
		// we adjust the weight of the block so entities cannot go up if they intersect with only 1 pixel
		fr.left += 13;
		fr.width -= 20;

		if (this->mBody.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}

bool Entity::IsAboveOrOnLadder()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::getCurrentLevel()->mLadders)
	{
		sf::FloatRect fr = entity->mBody.getGlobalBounds();
		fr.top -= this->mBody.getTexture()->getSize().y + 10;
		fr.height += 13;
		if (this->mBody.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}

bool Entity::hitBlocks() {
	for (std::shared_ptr<Entity> entity : LevelFactory::getCurrentLevel()->mBlocks)
	{   
		if (this->mBody.getGlobalBounds().intersects(entity->mBody.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

bool Entity::notTouchingFloor()
{
	bool OnEdge = true;
	for (std::shared_ptr<Entity> entity : LevelFactory::getCurrentLevel()->mBlocks)
	{
		sf::FloatRect fr = entity->mBody.getGlobalBounds();
		fr.top -= 5;
		fr.left += 5;
		fr.width -= 10;
		if (mBody.getGlobalBounds().intersects(fr))
		{
			OnEdge = false;
		}
	}
	return !IsOnLadder() && OnEdge;
}

bool Entity::isOutOfPlayZone()
{
	return (this->mBody.getPosition().y > 600) ? true : false;
}

void Entity::updateTexture(std::string path)
{
	mTexture.loadFromFile(path);
	// std::cout<<"path ="<<path<<"\n";
	mBody.setTexture(mTexture);
}
