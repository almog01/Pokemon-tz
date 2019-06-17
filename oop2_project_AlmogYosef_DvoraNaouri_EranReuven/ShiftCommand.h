#pragma once
#include "Command.h"
class ShiftCommand : public Command
{
public:
	ShiftCommand();
	~ShiftCommand();

	// Inherited via Command
	virtual void execute() override;
};

