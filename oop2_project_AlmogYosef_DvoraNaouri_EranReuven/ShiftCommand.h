#pragma once
#include "Command.h"
#include "PokemonList.h"
class ShiftCommand : public Command // inherit from Command
{
public:
	ShiftCommand(int index, int & nextPokemon); // constructor
	~ShiftCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command

private:
	int m_index; //index member of the pokemon
	int & m_nextPokemon; //next pokemon index reference
};