#include "InstructionsCommand.h"
#include "InstructionScreen.h"



InstructionsCommand::InstructionsCommand(std::unique_ptr<Screen> &subScreen)
	:m_subScreen(subScreen)
{
}


InstructionsCommand::~InstructionsCommand()
{
}

void InstructionsCommand::execute()
{
	m_subScreen = std::make_unique<InstructionScreen>();
}
