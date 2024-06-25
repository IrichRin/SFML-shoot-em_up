#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Resources/ResourceHolder.hpp"
#include "../Resources/SceneNode.h"

#include "World.h"

//Entities
#include "../Entities/Aircraft.h"
#include "../Entities/Player.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	ResourceHolder<sf::Font, Fonts::ID> mFonts;
	ResourceHolder<sf::Texture, Textures::ID> mTextures;

	sf::RenderWindow mWindow;

	World mWorld; 
	Player mPlayer;

private:

	void processInput();

	void update(sf::Time delta);
	void render();


};

