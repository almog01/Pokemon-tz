#pragma once
#include "Command.h"
class SaveCommand :	public Command
{
public:
	SaveCommand();
	~SaveCommand();

	// Inherited via Command
	virtual void execute() override;
};

