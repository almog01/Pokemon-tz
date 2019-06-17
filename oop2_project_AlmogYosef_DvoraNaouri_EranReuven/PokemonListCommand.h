#pragma once
#include "Command.h"
#include "Screen.h"
#include "Trainer.h"

using std::unique_ptr;

class PokemonListCommand :	public Command
{
public:
	PokemonListCommand(unique_ptr<Screen> & screen, Trainer & trainer, bool inBattle = false);
	~PokemonListCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	bool m_inBattle;
	unique_ptr<Screen> & m_screen;
	Trainer & m_trainer;
};

