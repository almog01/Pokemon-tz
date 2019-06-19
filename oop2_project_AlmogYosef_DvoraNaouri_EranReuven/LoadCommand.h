#pragma once
#include "Command.h"
#include "StartMenu.h"
#include "Player.h"
#include <fstream>

using std::ifstream;
using std::istringstream;

class LoadCommand :
	public Command
{
public:
	LoadCommand(StartMenu& startm, Player& player);
	~LoadCommand();

	// Inherited via Command
	virtual void execute() override;
private:
	Player& m_player;
	StartMenu& m_startm;

};

