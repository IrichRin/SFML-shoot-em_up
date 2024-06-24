#pragma once

#include <SFML/Window/Event.hpp>

#include "../Input/CommandQueue.h"
#include "Aircraft.h"

class Player
{
public:
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& command);
};

