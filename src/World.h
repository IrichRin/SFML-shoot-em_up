#pragma once
#include "include/Resources/ResourceHolder.hpp"
#include "include/Resources/SceneNode.h"
#include "include/Resources/SpriteNode.h"
#include "include/Entities/Aircraft.h"
#include <array>

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

private: 
	sf::RenderWindow& mWindow; 
	sf::View mWorldView;
	TextureHolder mTextures;
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers; 

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition; 
	float mScrollSpeed; 
	Aircraft* mPlayerAircraft;
	
private:
	void loadTexture();
	void buildScene();

};

