#pragma once
#include "Command.h"
#include "Player.h"
#include <fstream>

using std::ofstream;
using std::stringstream;

class SaveCommand :	public Command
{
public:
	SaveCommand(Player& player);
	~SaveCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	Player& m_player;
};

