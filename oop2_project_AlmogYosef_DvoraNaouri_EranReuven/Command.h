#pragma once
#include <SFML/Graphics.hpp>

class Command //main command class, abstract class
{
public:
	Command() {}; //constructor
	virtual ~Command() {}; //virtual destructor for polymorph

	virtual void execute() = 0; //abstract virtual execute class
};

