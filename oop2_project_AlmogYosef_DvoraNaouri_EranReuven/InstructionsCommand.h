#pragma once
#include "Command.h"
#include "Screen.h"
class InstructionsCommand :	public Command //inherit from Command
{
public:
	InstructionsCommand(std::unique_ptr<Screen> &subScreen); //constructor
	~InstructionsCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command

private:
	std::unique_ptr<Screen> &m_subScreen; //reference to subscreen type. will be the
								          //instructions screen
};

