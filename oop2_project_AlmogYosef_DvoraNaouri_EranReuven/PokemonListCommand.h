#pragma once
#include "Command.h"
#include "Screen.h"
#include "Trainer.h"
#include "PokemonList.h"

using std::unique_ptr;

class PokemonListCommand :	public Command // inherit from Command
{
public:
	PokemonListCommand(unique_ptr<Screen> & screen, Trainer & trainer, int & nextPokemon, bool inBattle = false); //constructor
	~PokemonListCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command

private:
	bool m_inBattle; //boolian to figure if we are in a battle
	unique_ptr<Screen> & m_screen; //screen reference pointer
	Trainer & m_trainer; //trainter reference pointer
	int & m_nextPokemon; //next pokemon index reference
};

