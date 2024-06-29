#pragma once
#include "State.h"
#include "../Game/World.h"
#include "../Entities/Player.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& ev);

private:
	World mWorld;
	Player& mPlayer;
};

