#pragma once

#include <SFML/Window/Event.hpp>
#include <map>

#include "../Input/CommandQueue.h"
#include "Aircraft.h"

class Player
{
public:
	enum Action {
		moveLeft,
		moveRight,
		moveUp,
		moveDown
	};

	float mPlayerSpeed; 

public:
	Player();

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& command);

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding; 

private:
	static bool isRealTimeAction(Action action);
};

