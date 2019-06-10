#pragma once
#include <unordered_map>
#include <memory>
#include <fstream>
#include "Map.h"
#include "Collider.h"
#include "Move.h"
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

	static Map * map(const string & key);
	static Pokemon pokemon(const string & key);

private:
	Factory();
	void createMaps();
	void createDoors();
	void createNPCs();
	void createMoves();
	void createPokemons();

	static unordered_map<string, unique_ptr<Map>> m_maps;	// maps
	static unordered_map < string, unique_ptr<Move>> m_moves;
	static unordered_map < string, unique_ptr<Pokemon>> m_pokemons;
	ifstream m_file;
};

