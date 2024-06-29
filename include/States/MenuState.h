#pragma once
#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& ev);

	void updateOptionText();

private:
	enum OptionNames 
	{
		Play,
		Exit
	};
	
private:
	sf::Sprite mBackgroundSprite;

	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;

};

