#pragma once
#include "Command.h"
#include "Menu.h"
#include "StartMenu.h"

class startCommand :
	public Command
{
public:
	startCommand(StartMenu& startmenu);
	~startCommand();

	// Inherited via Command
	virtual void execute() override;
private:
	StartMenu& m_startmenu;
};

