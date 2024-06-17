#pragma once
#include <iostream>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "include/Resources/ResourceHolder.hpp"

namespace Textures {
	enum ID {
		Airplane, 
		Landscape
	};
}

namespace Fonts
{
	enum ID {
		ArcadeClassic
	};
}

class Game
{

public:
	Game();
	~Game();

	void run();

private:
	void loadFonts();
	void loadTextures();

	void handleInput(sf::Keyboard::Key key, bool isPressed);

	void pollEvent();
	void update(sf::Time delta);
	void render();

private:
	ResourceHolder<sf::Font, Fonts::ID> mFonts;
	ResourceHolder<sf::Texture, Textures::ID> mTextures;

	sf::RenderWindow mWindow;

	//fps 
	sf::Text mFPS; 

	//----player elements----//
	sf::Sprite mPlayer;

	bool mIsMovingUp; 
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;

	float mSpeed; 


};
