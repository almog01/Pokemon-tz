#include "Factory.h"
#include "Door.h"
#include "NPC.h"
#include "TrainerNPC.h"
#include "NurseNPC.h"
#include <sstream>

using std::make_unique;
using std::istringstream;
using std::getline;

unordered_map<string, unique_ptr<Map>> Factory::m_maps;
unordered_map<string, unique_ptr<Ability>> Factory::m_abilities;
unordered_map<string, unique_ptr<Pokemon>> Factory::m_pokemons;

Factory::Factory()
{
	// create all
	createMaps();
	createDoors();
	createAbilities();
	createPokemons();
	createNPCs();
	createSpecialNPCs();
	createTrainers();
}

Factory & Factory::instance()
{
	static Factory inst;
	return inst;
}

Factory::~Factory()
{
}

Map * Factory::map(const string & name)
{
	return m_maps.at(name).get();
}

Ability * Factory::ability(const string & name)
{
	return m_abilities.at(name).get();
}

Pokemon Factory::pokemon(const string & name)
{
	return *m_pokemons.at(name).get();
}

Pokemon Factory::pokemon(const string & name, int level)
{
	// inorder to return a pokemon with a specific level
	auto p = m_pokemons.at(name).get();
	p->setLevel(level);
	return *p;
}

void Factory::createMaps()
{
	// open maps file and create the maps based on it
	m_file.open("database/maps.txt");
	string name;
	while (getline(m_file, name))
		m_maps[name] = make_unique<Map>(name);
	m_file.close();
}

void Factory::createDoors()
{
	// open doors file and create the doors based on it
	m_file.open("database/doors.txt");
	string mapName;	// the map to add the door to
	while (getline(m_file, mapName))
	{
		int numOfDoors;	// number of doors in the current map
		m_file >> numOfDoors;
		m_file.get();
		for (int i = 0; i < numOfDoors; ++i)
		{
			// read door data than create it in the maps colliders
			string line;
			getline(m_file, line);
			istringstream stream(line);
			float sizeX, sizeY, destX, destY;
			string dest;
			int index;
			stream >> sizeX >> sizeY >> dest >> destX >> destY >> index;
			m_maps[mapName]->addCollider(make_unique<Door>(Vector2f(sizeX, sizeY), dest, Vector2f(destX, destY)), index);
		}
	}
	m_file.close();
}

void Factory::createAbilities()
{
	// open abilities file and create the abilities based on it
	m_file.open("database/abilities.txt");
	string line;
	while (getline(m_file, line))
	{
		// read ability data than create it in the abilities unordered map
		istringstream stream(line);
		string name, element;
		int damage, speed;
		stream >> name >> element >> damage >> speed;
		m_abilities[name] = make_unique<Ability>(name, element, damage, speed);
	}
	m_file.close();
}

void Factory::createPokemons()
{
	// open pokemons file and create the pokemons based on it
	m_file.open("database/pokemons.txt");
	string name;
	while (getline(m_file, name))
	{
		// read pokemon data than create it in the pokemons unordered map
		auto pokemon = std::make_unique<Pokemon>(name);
		istringstream stream;
		string line;
		getline(m_file, line);
		stream.str(line);
		string abilityName;
		while (stream >> abilityName)
			pokemon->addAbility(Factory::ability(abilityName));

		getline(m_file, line);
		stream.clear();
		stream.str(line);
		string element;
		int maxHp;
		stream >> element >> maxHp;
		pokemon->setElement(element);
		pokemon->setMaxHp(maxHp).setHp(maxHp);

		m_pokemons[name] = std::move(pokemon);

		getline(m_file, line);
		stream.clear();
		stream.str(line);
		string mapName;
		while (stream >> mapName)
			m_maps[mapName]->addWildPokemon(Factory::pokemon(name));	// add a copy of the pokemon to the map
	}
	m_file.close();
}

void Factory::createNPCs()
{
	// open npcs file and create the npcs based on it
	m_file.open("database/npcs.txt");
	string mapName;
	while (getline(m_file, mapName))
	{
		int numOfNPCs;	// number of npcs in the map
		m_file >> numOfNPCs;
		m_file.get();
		for (int i = 0; i < numOfNPCs; ++i)
		{
			// read npc data than create it in the map collider
			string line;
			getline(m_file, line);
			istringstream stream(line);
			int index;
			string name;
			stream >> name >> index;
			auto npc = make_unique<NPC>(name);
			getline(m_file, line);
			npc->setChat(line);
			m_maps[mapName]->addCollider(std::move(npc), index);
		}
	}
	m_file.close();
}

void Factory::createSpecialNPCs()
{
	// the nurse is a special npc that can also restore the player's pokemon to full health
	auto nurse = make_unique<NurseNPC>("nurse");
	nurse->setChat("I've restored your Pokemons to full health! We hope to see you again!");
	m_maps["pharmacy"]->addCollider(std::move(nurse), 0);
}

void Factory::createTrainers()
{
	// open trainers file and create the trainers based on it
	m_file.open("database/trainers.txt");
	string mapName;
	while (getline(m_file, mapName))
	{
		int numOfTrainers;	// number of trainers in the map
		m_file >> numOfTrainers;
		m_file.get();
		for (int i = 0; i < numOfTrainers; ++i)
		{
			// read trainer data than create it in the map collider
			string line;
			getline(m_file, line);
			istringstream stream(line);
			int index;
			string name;
			stream >> name >> index;
			auto trainer = make_unique<TrainerNPC>(name);
			getline(m_file, line);
			stream.clear();
			stream.str(line);
			string pokemonName;
			while (stream >> pokemonName)
			{
				int level;
				stream >> level;
				trainer->addPokemon(Factory::pokemon(pokemonName, level));
			}
			m_maps[mapName]->addCollider(std::move(trainer), index);
		}
	}
	m_file.close();
}