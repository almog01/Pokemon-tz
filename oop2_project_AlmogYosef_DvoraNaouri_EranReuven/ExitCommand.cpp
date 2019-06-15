#include "ExitCommand.h"


ExitCommand::ExitCommand(Menu & menu) : m_menu(menu)
{
}

ExitCommand::~ExitCommand()
{
}

void ExitCommand::execute()
{
	m_menu.deactivate();
}
