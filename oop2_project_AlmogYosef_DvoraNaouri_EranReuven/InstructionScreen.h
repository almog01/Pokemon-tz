#pragma once
#include "Screen.h"
class InstructionScreen : public Screen // inherit from Screen
{
public:
	InstructionScreen(); //constructor
	~InstructionScreen(); //destructor

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override; //draw function, override Screen virtual func
	virtual void keyReleasedHandler(const Event & event) override; //KeyReleasedHandler function, override Screen virtual func

private:
	sf::View m_view; //member to change the screen view
};

