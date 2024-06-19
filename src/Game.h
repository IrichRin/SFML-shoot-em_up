#pragma once
#include <SFML/Graphics.hpp>
#include "include/Resources/ResourceHolder.hpp"
#include "include/Resources/SceneNode.h"

#include "World.h"

//Entities
#include "include/Entities/Aircraft.h"

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

private:

	void handleInput(sf::Keyboard::Key key, bool isPressed);

	void pollEvent();
	void update(sf::Time delta);
	void render();


};

