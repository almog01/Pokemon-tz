#pragma once
#include "Command.h"
class BagCommand : public Command
{
public:
	BagCommand();
	~BagCommand();

	// Inherited via Command
	virtual void execute() override;
};

