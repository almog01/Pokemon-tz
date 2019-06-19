#pragma once
#include "Command.h"
#include "PokemonList.h"
class ShiftCommand : public Command
{
public:
	ShiftCommand(int index, int & nextPokemon);
	~ShiftCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	int m_index;
	int & m_nextPokemon;
};