#include "ShiftCommand.h"



ShiftCommand::ShiftCommand(int index, int & nextPokemon)
	: m_index(index), m_nextPokemon(nextPokemon)
{
}


ShiftCommand::~ShiftCommand()
{
}

void ShiftCommand::execute()
{
	m_nextPokemon = m_index;
}
