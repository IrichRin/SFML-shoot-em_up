#pragma once

#include "../States/StateStack.h"
#include "../Resources/ResourceHolder.hpp"
#include "../Entities/Player.h"
#include "../Resources/ResourceIdentifier.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application
{
public:
	Application();

	void run();

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	TextureHolder mTextures;
	FontHolder mFonts;
	Player mPlayer;

	StateStack mStateStack;

	sf::Text mFPS;
	sf::Time mFPSTime;
	std::size_t	mFPSNumFrames;

private:
	void processInput();
	void updateFPS(sf::Time elapsedTime);

	void update(sf::Time delta);
	void render();

	void registerStates();
};

