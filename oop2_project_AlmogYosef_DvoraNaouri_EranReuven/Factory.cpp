#include "Factory.h"
#include "City.h"
#include "House.h"
#include "Door.h"
#include "NPC.h"
#include <sstream>

using std::make_unique;
using std::istringstream;
using std::getline;

unordered_map<string, unique_ptr<Map>> Factory::m_maps{};

Map * Factory::map(const string & key)
{
	return m_maps.at(key).get();
}

Factory::Factory()
{
	createMaps();
	createDoors();
	createNPCs();
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
		int numOfNPCs;
		m_file >> numOfNPCs;
		m_file.get();
		for (int i = 0; i < numOfNPCs; ++i)
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
		int numOfDoors;
		m_file >> numOfDoors;
		m_file.get();
		for (int i = 0; i < numOfDoors; ++i)
		{
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

Factory & Factory::instance()
{
	static Factory inst;
	return inst;
}

Factory::~Factory()
{
}
