#include "Aircraft.h"

Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::red:
		return Textures::red;

	case Aircraft::pewpew:
		return Textures::pewpew; 
		
	default: 
		return Textures::red;
	}

}

Aircraft::Aircraft(Type type, TextureHolder& textures)
	: mType(type),
	mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	this->mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->mSprite, states);
}
