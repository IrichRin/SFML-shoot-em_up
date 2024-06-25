	#include "../include/Game/Game.h"

Game::Game()
	: mWindow(sf::VideoMode(256, 300), "shoot-em up"),
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
		
		timeSinceLastUpdate += clock.restart();
		while(timeSinceLastUpdate > sf::seconds(1.f/144.f))
		{
			timeSinceLastUpdate -= sf::seconds(1.f/144.f);

			processInput();
			update(sf::seconds(1.f/144.f));
		}
		render();
	}
}

//----PRIVATE FUNCTIONS----//

void Game::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

	sf::Event ev; 
	while (mWindow.pollEvent(ev))
	{
		mPlayer.handleEvent(ev, commands);

		if (ev.type == sf::Event::Closed)
			mWindow.close();
		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			mWindow.close();
	}

	mPlayer.handleRealtimeInput(commands);
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
