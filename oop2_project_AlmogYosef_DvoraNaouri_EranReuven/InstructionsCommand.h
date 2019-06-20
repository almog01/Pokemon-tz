#pragma once
#include "Command.h"
class InstructionsCommand :
	public Command
{
public:
	InstructionsCommand();
	~InstructionsCommand();

	// Inherited via Command
	virtual void execute() override;

};

