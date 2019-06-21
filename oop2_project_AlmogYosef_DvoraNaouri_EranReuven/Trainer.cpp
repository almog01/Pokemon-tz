#include "Trainer.h"



Trainer::Trainer()
{
}


Trainer::~Trainer()
{
}

void Trainer::healPokemons()
{
	for (auto& pokemon : m_pokemons)
		pokemon->setHp(pokemon->getMaxHp());
}

bool Trainer::isDefeated() const
{
	for (auto & pokemon : m_pokemons)
		if (pokemon->getHp() > 0)
			return false;
	return true;
}
