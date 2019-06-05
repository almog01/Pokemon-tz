#include "Factory.h"
#include "City.h"
#include "House.h"
#include "Door.h"

using std::make_unique;

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
	m_file.open("database/maps.txt");
	m_maps["pallet"] = make_unique<City>("pallet");
	m_maps["pallet"]->addCollider(make_unique<Door>("oaks_lab", Vector2f(16.f, 17.f)));
	m_maps["oaks_lab"] = make_unique<House>("oaks_lab");
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
