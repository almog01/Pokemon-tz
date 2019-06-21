#pragma once
#include "Command.h"
#include "Screen.h"
class InstructionsCommand :
	public Command
{
public:
	InstructionsCommand(std::unique_ptr<Screen> &subScreen);
	~InstructionsCommand();

	// Inherited via Command
	virtual void execute() override;
private:
	std::unique_ptr<Screen> &m_subScreen;

};

