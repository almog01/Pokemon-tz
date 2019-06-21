#pragma once
#include <unordered_map>
#include <memory>
#include <fstream>
#include "Map.h"
#include "Collider.h"
#include "Ability.h"
#include "Pokemon.h"

using std::string;
using std::unordered_map;
using std::unique_ptr;
using std::ifstream;

class Factory
{
public:
	// Singleton Factory
	static Factory& instance();
	~Factory();
	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;

	// function to get by name each type of created object: map, ability and pokemon
	static Map * map(const string & name);
	static Ability * ability(const string & name);
	static Pokemon pokemon(const string & name);
	static Pokemon pokemon(const string & name, int level);

private:
	Factory();	// c-tor

	// function to create each type of object in the game
	void createMaps();
	void createDoors();
	void createAbilities();
	void createPokemons();
	void createNPCs();
	void createSpecialNPCs();
	void createTrainers();

	static unordered_map<string, unique_ptr<Map>> m_maps;			// maps
	static unordered_map <string, unique_ptr<Ability>> m_abilities;	// abilities
	static unordered_map <string, unique_ptr<Pokemon>> m_pokemons;	// pokemons
	ifstream m_file;	// file to read and create all the objects
};

