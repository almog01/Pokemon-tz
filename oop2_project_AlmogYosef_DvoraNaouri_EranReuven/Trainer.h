#pragma once
#include "Pokemon.h"
#include <iterator>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::iterator;
using std::random_access_iterator_tag;

class Trainer //Trainter class for characters that having pokemons
{
public:
	Trainer(); //constructor
	virtual ~Trainer(); //destructor

	//add pokemon function into the vector
	void addPokemon(Pokemon pokemon) { m_pokemons.emplace_back(make_shared<Pokemon>(pokemon)); }

	bool isDefeated() const; //bolian to check if the trainer as been defeated

	//iterators settings to run over the pokemons vector
	vector<shared_ptr<Pokemon>>::iterator begin() { return m_pokemons.begin(); }
	vector<shared_ptr<Pokemon>>::iterator end() { return m_pokemons.end(); }
	vector<shared_ptr<Pokemon>>::const_iterator cbegin() { return m_pokemons.cbegin(); }
	vector<shared_ptr<Pokemon>>::const_iterator cend() { return m_pokemons.cend(); }

private:
	vector<shared_ptr<Pokemon>> m_pokemons; //pokemons vector
};
