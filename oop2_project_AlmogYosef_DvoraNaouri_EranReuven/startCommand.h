#pragma once
#include "Command.h"
#include "Menu.h"
#include "StartMenu.h"
#include "GameManager.h"

class StartCommand : 
	public Command // inherit from Command
{
public:
	StartCommand(StartMenu& startmenu); //constructor
	~StartCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command
private:
	StartMenu& m_startmenu; //start menu reference to be able to close it.
};

