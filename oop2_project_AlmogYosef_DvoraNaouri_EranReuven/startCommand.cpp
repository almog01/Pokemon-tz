#include "startCommand.h"


startCommand::startCommand(StartMenu& startmenu)
	:m_startmenu(startmenu)
{
}

startCommand::~startCommand()
{
}

void startCommand::execute()
{
	m_startmenu.deactivate();
}
