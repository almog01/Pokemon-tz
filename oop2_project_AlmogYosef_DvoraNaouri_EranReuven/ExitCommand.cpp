#include "ExitCommand.h"

/* constructor  will init the screen pointer and the main screen boolian. 
default value is false. if the main screen send exit command, it will
send it with true, to exit the whole game.*/
ExitCommand::ExitCommand(Screen * screen, bool isMainScreen) 
	: m_screen(screen), m_isMain(isMainScreen)
{
}

ExitCommand::~ExitCommand() //destructor
{
}

void ExitCommand::execute()
{
	if (m_isMain) //if its the main screen exit command, exit the game
		exit(EXIT_SUCCESS);
	m_screen->deactivate(); //default exit command, close the menu.
}
