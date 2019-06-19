#include "Trainer.h"



Trainer::Trainer()
{
}


Trainer::~Trainer()
{
}

bool Trainer::isDefeated() const
{
	for (auto & pokemon : m_pokemons)
		if (pokemon->getHp() > 0)
			return false;
	return true;
}
