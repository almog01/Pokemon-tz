#pragma once
#include "Command.h"
#include "StartMenu.h"
#include "Player.h"
#include <fstream>

using std::ifstream;
using std::istringstream;

class LoadCommand :
	public Command // inherit from Command
{
public:
	LoadCommand(StartMenu& startm, Player& player); //constructor
	~LoadCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command
private:
	Player& m_player; //player reference to load player condition
	StartMenu& m_startm; //start menu reference to be able to close it.

};

