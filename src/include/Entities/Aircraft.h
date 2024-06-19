#pragma once
#include "Entity.h"
#include "../Resources/ResourceHolder.hpp"



class Aircraft : public Entity
{

public:
	enum Type 
	{
		red, 
		pewpew
	};

public:
	explicit Aircraft(Type type, TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 

private: 
	Type mType; 
	sf::Sprite mSprite; 
};

