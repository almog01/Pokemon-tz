#include "ExitCommand.h"


ExitCommand::ExitCommand(Screen * screen) : m_screen(screen)
{
}

ExitCommand::~ExitCommand()
{
}

void ExitCommand::execute()
{
	m_screen->deactivate();
}
