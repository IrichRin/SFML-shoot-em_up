#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	this->mVelocity.x = vx; 
	this->mVelocity.y = vy; 
}

sf::Vector2f Entity::getVelocity() const
{
	return this->mVelocity;
}

void Entity::updateCurrent(sf::Time dt)
{
	this->move(this->mVelocity * dt.asSeconds());
}
