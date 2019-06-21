#pragma once
#include "Command.h"
#include "Screen.h"

class ExitCommand : public Command
{
public:
	ExitCommand(Screen * screen, bool isMainScreen = false);
	~ExitCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	bool m_isMain;
	Screen * m_screen;
};

