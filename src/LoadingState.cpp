#include "../include/States/LoadingState.h"
#include "../include/Resources/ResourceHolder.hpp"
#include "../include/Resources/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

LoadingState::LoadingState(StateStack& state, State::Context context)
	: State (state, context),
	mLoadingTask(),
	mProgressBar(),
	mProgressBarBackground()
{
	sf::RenderWindow& window = *getContext().window;
	sf::Font& font = context.fonts->get(Fonts::ArcadeClassic);
	sf::Vector2f viewSize = window.getView().getSize();
		
	mLoadingText.setFont(font);
	mLoadingText.setString("Loading Resources");
	centerOrigin(mLoadingText);
	mLoadingText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 50.f);

	mProgressBarBackground.setFillColor(sf::Color::White);
	mProgressBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10));
	mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);

	mProgressBarBackground.setFillColor(sf::Color(100,100,100));
	mProgressBarBackground.setSize(sf::Vector2f(200, 10));
	mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);

	setCompletion(0.f);

	mLoadingTask.execute();
}

void LoadingState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mLoadingText);
	window.draw(mProgressBarBackground);
	window.draw(mProgressBar);
}

bool LoadingState::update(sf::Time dt)
{
	if (mLoadingTask.isFinished())
	{
		requestStackPop();
		requestStackPush(States::Game);
	}
	else
	{
		setCompletion(mLoadingTask.getCompletion());
	}

	return true;
}

bool LoadingState::handleEvent(const sf::Event ev)
{
	return true;
}

void LoadingState::setCompletion(float percent)
{
	if (percent > 1.f)
		percent = 1.f;

	mProgressBar.setSize(sf::Vector2f(mProgressBarBackground.getSize().x * percent, 
		mProgressBar.getSize().y));
}
