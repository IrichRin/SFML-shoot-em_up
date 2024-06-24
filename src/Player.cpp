#include "include/Entities/Player.h"
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

void Player::handleRealtimeInput(CommandQueue& command)
{
	const float playerSpeed = 150.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0));
		command.push(moveLeft);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0));
		command.push(moveRight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Command moveUp;
		moveUp.category = Category::PlayerAircraft;
		moveUp.action = derivedAction<Aircraft>(AircraftMover(0, -playerSpeed));
		command.push(moveUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Command moveDown;
		moveDown.category = Category::PlayerAircraft;
		moveDown.action = derivedAction<Aircraft>(AircraftMover(0, playerSpeed));
		command.push(moveDown);
	}
}
