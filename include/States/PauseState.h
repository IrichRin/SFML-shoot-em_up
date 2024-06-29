#pragma once
#include "State.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& ev);

private:
	sf::Sprite mBackgroundSprite;
	sf::Text mPausedText;
	sf::Text mInstructionText;

};
