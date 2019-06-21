#include "InstructionsCommand.h"
#include "InstructionScreen.h"

//constructor will init the subscreen reference, to keep it avilable after creation
InstructionsCommand::InstructionsCommand(std::unique_ptr<Screen> &subScreen)
	: m_subScreen(subScreen)
{
}


InstructionsCommand::~InstructionsCommand() //destructor
{
}

void InstructionsCommand::execute()
{
	m_subScreen = std::make_unique<InstructionScreen>(); //creating the Instructions Screen
}
