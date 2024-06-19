#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
	sf::Sprite mSprite;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 

};

