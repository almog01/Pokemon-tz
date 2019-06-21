#pragma once
#include "Command.h"
#include "Player.h"
#include "Screen.h"
#include <fstream>

using std::unique_ptr;
using std::ofstream;
using std::stringstream;
using sf::RenderWindow;

class SaveCommand :	public Command // inherit from Command
{
public:
	SaveCommand(Player& player, unique_ptr<Screen> & screen, RenderWindow & window); //constructor
	~SaveCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command
	Player& m_player; //player reference
	unique_ptr<Screen> & m_screen; //screen reference
	RenderWindow & m_window; //window reference
};

