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
}

void Factory::createMaps()
{
	/*m_file.open("database/maps.txt");
	string line;
	getline(m_file, line);
	istringstream stream(line);
	string name;
	int numOfColliders;
	stream >> name >> numOfColliders;
	m_maps[name] = make_unique<Map>("pallet");
	for (size_t i = 0; i < numOfColliders; i++)
	{
		getline(m_file, line);

	}*/

	m_maps["pallet"] = make_unique<City>("pallet");
	m_maps["pallet"]->addCollider(make_unique<Door>(Vector2f(16.f, 17.f), "oaks_lab", Vector2f(97.f, 180.f)));
	m_maps["oaks_lab"] = make_unique<House>("oaks_lab");
	m_maps["oaks_lab"]->addCollider(make_unique<NPC>("professor_oak"));
	m_maps["oaks_lab"]->addCollider(make_unique<Door>(Vector2f(26.f, 4.f), "pallet", Vector2f(256.f, 560.f)));
	//m_maps["vermillion"] = make_unique<City>("vermillion");
}


Factory & Factory::instance()
{
	static Factory inst;
	return inst;
}

Factory::~Factory()
{
}
