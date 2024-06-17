#pragma once
#include <SFML/Graphics.hpp>

//base class for entities

class Entity
{
public: 
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);

	sf::Vector2f getVelocity() const; 

private: 
	sf::Vector2f mVelocity;
};
