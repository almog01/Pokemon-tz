#include "Factory.h"
#include "City.h"
#include "House.h"
#include "Door.h"
#include "NormalNPC.h"
#include <sstream>

using std::make_unique;
using std::istringstream;
using std::getline;

unordered_map<string, unique_ptr<Map>> Factory::m_maps;
unordered_map<string, unique_ptr<Ability>> Factory::m_abilities;
unordered_map<string, unique_ptr<Pokemon>> Factory::m_pokemons;

Factory::Factory()
{
	createMaps();
	createDoors();
	createNPCs();
	createAbilities();
	createPokemons();
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

void Factory::createMaps()
{
	m_file.open("database/maps.txt");
	string name;
	while (getline(m_file, name))
		m_maps[name] = make_unique<Map>(name);
	m_file.close();
}

void Factory::createDoors()
{
	m_file.open("database/doors.txt");
	string mapName;
	while (getline(m_file, mapName))
	{
		int numOfDoors;
		m_file >> numOfDoors;
		m_file.get();
		for (int i = 0; i < numOfDoors; ++i)
		{
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

void Factory::createNPCs()
{
	m_file.open("database/npcs.txt");
	string mapName;
	while (getline(m_file, mapName))
	{
		int numOfNPCs;
		m_file >> numOfNPCs;
		m_file.get();
		for (int i = 0; i < numOfNPCs; ++i)
		{
			string line;
			getline(m_file, line);
			istringstream stream(line);
			int index;
			string name;
			stream >> name >> index;
			auto npc = make_unique<NormalNPC>(name);
			getline(m_file, line);
			npc->setChat(line);
			m_maps[mapName]->addCollider(std::move(npc), index);
		}
	}
	m_file.close();
}

void Factory::createAbilities()
{
	m_file.open("database/abilities.txt");
	string line;
	while (getline(m_file, line))
	{
		istringstream stream(line);
		string name, element;
		int damage, speed;
		stream >> name >> element >> damage >> speed;
		m_abilities[name] = make_unique<Ability>(name, Ability::stringToElement(element), damage, speed);
	}
	m_file.close();
}

void Factory::createPokemons()
{
	m_file.open("database/pokemons.txt");
	string name;
	while (getline(m_file, name))
	{
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
		while (stream >> element)
			pokemon->setElement(Ability::stringToElement(element));

		int maxHp;
		bool canFly;
		getline(m_file, line);
		stream.clear();
		stream.str(line);
		stream >> maxHp >> canFly;
		pokemon->setMaxHp(maxHp).setHp(maxHp).setCanFly(canFly);
		m_pokemons[name] = std::move(pokemon);
	}
	m_file.close();
}
