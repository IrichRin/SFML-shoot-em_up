#include "Game.h"

Game::Game()
	: mWindow(sf::VideoMode(350, 300), "shoot-em up"),
	mWorld(mWindow)
{

}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (mWindow.isOpen())
	{
		pollEvent();
		timeSinceLastUpdate += clock.restart();
		while(timeSinceLastUpdate > sf::seconds(1.f/144.f))
		{
			timeSinceLastUpdate -= sf::seconds(1.f/144.f);
			pollEvent();
			update(sf::seconds(1.f/144.f));
		}
		render();
	}
}


void Game::handleInput(sf::Keyboard::Key key, bool isPressed)
{

}

//----PRIVATE FUNCTIONS----//
void Game::pollEvent()
{
	sf::Event ev;
	while (mWindow.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleInput(ev.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleInput(ev.key.code, false);
			break;
		}
	}
}

void Game::update(sf::Time delta)
{
	this->mWorld.update(delta);
}

void Game::render()
{
	this->mWindow.clear();
	this->mWorld.draw();

	this->mWindow.setView(mWindow.getDefaultView());
	this->mWindow.display();
}
