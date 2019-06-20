#pragma once
#include "Screen.h"
class InstructionScreen :
	public Screen
{
public:
	InstructionScreen();
	~InstructionScreen();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;

private:
	sf::View m_view;
};

