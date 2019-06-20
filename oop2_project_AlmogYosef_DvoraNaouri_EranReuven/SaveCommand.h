#pragma once
#include "Command.h"
#include "Player.h"
#include "Screen.h"
#include <fstream>

using std::unique_ptr;
using std::ofstream;
using std::stringstream;
using sf::RenderWindow;

class SaveCommand :	public Command
{
public:
	SaveCommand(Player& player, unique_ptr<Screen> & screen, RenderWindow & window);
	~SaveCommand();

	// Inherited via Command
	virtual void execute() override;
	Player& m_player;
	unique_ptr<Screen> & m_screen;
	RenderWindow & m_window;
};

