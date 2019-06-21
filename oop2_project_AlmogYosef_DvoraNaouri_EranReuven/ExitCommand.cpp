#include "ExitCommand.h"


ExitCommand::ExitCommand(Screen * screen, bool isMainScreen) : m_screen(screen), m_isMain(isMainScreen)
{
}

ExitCommand::~ExitCommand()
{
}

void ExitCommand::execute()
{
	if (m_isMain)
		exit(EXIT_SUCCESS);
	m_screen->deactivate();
}
