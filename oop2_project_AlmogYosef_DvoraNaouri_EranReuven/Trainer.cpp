#include "Trainer.h"



Trainer::Trainer() //constructor
{
}


Trainer::~Trainer() //destroctor
{
}

void Trainer::healPokemons()
{
	for (auto& pokemon : m_pokemons)
		pokemon->setHp(pokemon->getMaxHp());
}

bool Trainer::isDefeated() const
{
	for (auto & pokemon : m_pokemons) //run over the pokemon to figure if the trainer is deafeted
		if (pokemon->getHp() > 0)
			return false;
	return true;
}
