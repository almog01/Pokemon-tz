#include "InstructionsCommand.h"
#include "InstructionScreen.h"



InstructionsCommand::InstructionsCommand()
{
}


InstructionsCommand::~InstructionsCommand()
{
}

void InstructionsCommand::execute()
{
	std::make_unique<InstructionScreen>();
}
