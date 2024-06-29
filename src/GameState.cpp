#include "../include/states/GameState.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context),
	mWorld(*context.window),
	mPlayer(*context.player)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& ev)
{
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(ev, commands);

	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}
