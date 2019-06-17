#include "PokemonListCommand.h"
#include "PokemonList.h"

using std::make_unique;

PokemonListCommand::PokemonListCommand(unique_ptr<Screen> & screen, Trainer & trainer, bool inBattle)
	: m_screen(screen), m_trainer(trainer), m_inBattle(inBattle)
{
}


PokemonListCommand::~PokemonListCommand()
{
}

void PokemonListCommand::execute()
{
	m_screen = make_unique<PokemonList>(m_trainer, m_inBattle);
}

