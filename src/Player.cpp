#include "../include/Entities/Player.h"
#include <iostream>

struct AircraftMover {
	AircraftMover(float vx, float vy)
	: velocity(vx,vy)
	{
	}

	void operator() (SceneNode& node, sf::Time) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
	: mPlayerSpeed(150.f)
{
	mKeyBinding[sf::Keyboard::A] = moveLeft;
	mKeyBinding[sf::Keyboard::D] = moveRight;
	mKeyBinding[sf::Keyboard::W] = moveUp;
	mKeyBinding[sf::Keyboard::S] = moveDown;

	mActionBinding[moveLeft].action = derivedAction<Aircraft>(AircraftMover(-mPlayerSpeed, 0.f));
	mActionBinding[moveRight].action = derivedAction<Aircraft>(AircraftMover(mPlayerSpeed, 0.f));
	mActionBinding[moveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -mPlayerSpeed));
	mActionBinding[moveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, mPlayerSpeed));

	for(auto &pair : this->mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << "," << s.getPosition().y << "\n";
		};
		commands.push(output);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for (auto pair : this->mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
	case moveLeft:
	case moveRight:
	case moveUp:
	case moveDown:
		return true;
	default:
		return false;
	}
}
