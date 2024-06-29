#include "../include/Game/Application.h"
#include "../include/Resources/Utility.hpp"
#include "../include/States/State.h"
#include "../include/States/StateIdentifiers.hpp"
#include "../include/States/MenuState.h"
#include "../include/States/PauseState.h"
#include "../include/States/GameState.h"
#include "../include/States/TitleState.h"

#include <SFML/Graphics/Color.hpp>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/140.f);

Application::Application()
	: mWindow(sf::VideoMode(256, 272), "shoot-em up"),
	mTextures(),
	mFonts(),
	mPlayer(),
	mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer)),
	mFPS(),
	mFPSTime(),
	mFPSNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::ArcadeClassic, "assets/fonts/ARCADECLASSIC.ttf");
	mTextures.load(Textures::TitleScreen, "assets/background/bg.png");

	mFPS.setFont(mFonts.get(Fonts::ArcadeClassic));
	mFPS.setPosition(0, 0);
	mFPS.setCharacterSize(15);
	mFPS.setFillColor(sf::Color::White);


	registerStates();
	mStateStack.pushState(States::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
			
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateFPS(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event ev;
	while (mWindow.pollEvent(ev))
	{
		mStateStack.handleEvent(ev);

		if (ev.type == sf::Event::Closed)
			mWindow.close();
	}
	
}

void Application::updateFPS(sf::Time elapsedTime)
{
	mFPSTime += elapsedTime;
	mFPSNumFrames++;
	if (mFPSTime >= sf::seconds(1.f))
	{
		mFPS.setString("FPS Count: " + toString(mFPSNumFrames));

		mFPSNumFrames = 0; 
		mFPSTime -= sf::seconds(1.f);
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mFPS);
	mWindow.display();

}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
}
