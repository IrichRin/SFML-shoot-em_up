#pragma once
#include "Entity.h"

class Aircraft : public Entity
{

public:
	enum Type 
	{
		red, 
		pewpew
	};

public:
	explicit Aircraft(Type type);

private: 
	Type mType; 
};

