#pragma once
#include "State.h"
#include "StateStack.h"
#include "ParallelTask.h"

#include <SFML/Graphics/Text.hpp>
#include <SFMl/Graphics/RectangleShape.hpp>

class LoadingState : public State
{
public:
	LoadingState(StateStack& state, State::Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event ev);

	void setCompletion(float percent);

private:
	sf::Text mLoadingText;
	sf::RectangleShape mProgressBarBackground;
	sf::RectangleShape mProgressBar;

	ParallelTask mLoadingTask;
};

