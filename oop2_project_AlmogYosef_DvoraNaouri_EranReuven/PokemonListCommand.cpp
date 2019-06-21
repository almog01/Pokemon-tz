#include "PokemonListCommand.h"

using std::make_unique;

//will init the screen, trainer and next pokemon index references
PokemonListCommand::PokemonListCommand(unique_ptr<Screen> & screen, Trainer & trainer, int & nextPokemon, bool inBattle)
	: m_screen(screen), m_trainer(trainer), m_inBattle(inBattle), m_nextPokemon(nextPokemon)
{
}


PokemonListCommand::~PokemonListCommand()
{
}

void PokemonListCommand::execute()
{
	//will make the pokemon list screen
	m_screen = make_unique<PokemonList>(m_trainer, m_nextPokemon, m_inBattle);
}

