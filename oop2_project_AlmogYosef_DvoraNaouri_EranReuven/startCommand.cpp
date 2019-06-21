#include "StartCommand.h"

//start menu command constructor will init the reference
StartCommand::StartCommand(StartMenu& startmenu)
	:m_startmenu(startmenu)
{
}

StartCommand::~StartCommand()
{
}
//will close the start menu screen so the game can begin
void StartCommand::execute()
{
	m_startmenu.deactivate();
}
