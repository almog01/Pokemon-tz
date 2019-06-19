#pragma once
#include "Command.h"
#include "Screen.h"

class ExitCommand : public Command
{
public:
	ExitCommand(Screen * screen);
	~ExitCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	Screen * m_screen;
};

