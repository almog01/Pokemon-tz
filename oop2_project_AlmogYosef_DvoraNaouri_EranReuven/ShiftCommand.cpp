#include "ShiftCommand.h"


//constructor will init the index value, and next pokemon value reference
ShiftCommand::ShiftCommand(int index, int & nextPokemon)
	: m_index(index), m_nextPokemon(nextPokemon)
{
}


ShiftCommand::~ShiftCommand() //destructor
{
}

void ShiftCommand::execute()
{
	m_nextPokemon = m_index; //shifting to the next pokemon (chosen pokemon to shift)
}
