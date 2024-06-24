#pragma once
#include "../Resources/ResourceHolder.hpp"
#include "../Resources/SceneNode.h"
#include "../Resources/SpriteNode.h"
#include "../Entities/Aircraft.h"
#include "../Input/CommandQueue.h"
#include <array>

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();

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

	CommandQueue mCommandQueue; 
	
private:
	void loadTexture();
	void buildScene();
	void adaptPlayerPosition();

};

