#pragma once
#include <SFML/Graphics.hpp>

class Command
{
public:
	Command();
	virtual ~Command();

	virtual void execute() = 0;
};

