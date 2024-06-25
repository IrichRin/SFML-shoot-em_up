#include "../include/Input/CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	this->mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();

	return command; 
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
