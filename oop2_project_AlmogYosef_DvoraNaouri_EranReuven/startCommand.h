#pragma once
#include "Command.h"
#include "Menu.h"
#include "StartMenu.h"
#include "GameManager.h"

class StartCommand :
	public Command
{
public:
	StartCommand(StartMenu& startmenu);
	~StartCommand();

	// Inherited via Command
	virtual void execute() override;
private:
	StartMenu& m_startmenu;
};

