#include "../include/States/MenuState.h"
#include "../include/Resources/ResourceHolder.hpp"
#include "../include/Resources/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context),
	mOptions(),
	mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::ArcadeClassic);

	mBackgroundSprite.setTexture(texture);

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(playOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(-30, 30.f));
	mOptions.push_back(exitOption);

	updateOptionText();

}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);
	
	for (sf::Text& text : mOptions)
		window.draw(text);
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& ev)
{
	if (ev.type != sf::Event::KeyPressed)
		return false;

	if (ev.key.code == sf::Keyboard::Enter)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == Exit)
			requestStateClear();
	}

	else if (ev.key.code == sf::Keyboard::W)
	{
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}

	else if (ev.key.code == sf::Keyboard::S)
	{
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;

	for (sf::Text& text : mOptions)
		text.setFillColor(sf::Color::White);

	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}
