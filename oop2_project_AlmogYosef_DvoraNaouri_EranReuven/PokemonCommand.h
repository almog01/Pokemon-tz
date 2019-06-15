#pragma once
#include "Command.h"
class PokemonCommand :	public Command
{
public:
	PokemonCommand();
	~PokemonCommand();

	// Inherited via Command
	virtual void execute() override;
};

