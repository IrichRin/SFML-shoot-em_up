#include "../include/Entities/Aircraft.h"

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
	sf::Texture texture = textures.get(toTextureID(type));
	sf::Vector2u textureSize = texture.getSize();

	int temp = (type == Aircraft::Type::red) ? 24 : 16;
	int textX = textureSize.x / 16, textY = textureSize.y / temp;

	textureSize.x /= textX;
	textureSize.y /= textY;

	this->mSprite.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));

	sf::FloatRect bounds = mSprite.getLocalBounds();
	this->mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Aircraft::getCategory() const
{
	switch (this->mType)
	{
	case red: 
		return Category::PlayerAircraft;
	default:
		return Category::EnemyAircraft;
	}
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->mSprite, states);
}


