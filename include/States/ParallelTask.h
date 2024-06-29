#pragma once

#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>


class ParallelTask
{
public:
	ParallelTask();
	void execute();
	bool isFinished();
	float getCompletion();

private:
	sf::Thread	mThread;
	bool mFinished;
	sf::Clock mElapsedTime;
	sf::Mutex mMutex;
	
private:
	void runTask();

};

