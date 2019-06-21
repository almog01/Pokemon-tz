#pragma once
#include "Command.h"
#include "Screen.h"

class ExitCommand : public Command //inherit from Command
{
public:
	ExitCommand(Screen * screen, bool isMainScreen = false); //constructor
	~ExitCommand(); // destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command

private:
	bool m_isMain; //member to figure if the menu is the main menu. if yes,
				   //exit mean exit the game. otherwise, exit the menu.
	Screen * m_screen; //a pointer to the menu screen
};

