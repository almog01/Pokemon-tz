#pragma once
#include "Command.h"
#include "Menu.h"

class ExitCommand : public Command
{
public:
	ExitCommand(Menu & menu);
	~ExitCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	Menu & m_menu;
};

