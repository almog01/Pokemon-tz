#include "StartCommand.h"


StartCommand::StartCommand(StartMenu& startmenu)
	:m_startmenu(startmenu)
{
}

StartCommand::~StartCommand()
{
}

void StartCommand::execute()
{
	m_startmenu.deactivate();
}
