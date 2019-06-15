#pragma once
#include "Pokemon.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

class Trainer
{
public:
	Trainer();
	virtual ~Trainer();

	void addPokemon(Pokemon pokemon) { m_pokemons.emplace_back(make_shared<Pokemon>(pokemon)); }

	shared_ptr<Pokemon> getPokemon(int index) const { return m_pokemons.at(index); }

private:
	vector<shared_ptr<Pokemon>> m_pokemons;
};

