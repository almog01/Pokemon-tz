#pragma once
#include <unordered_map>
#include <memory>
#include <fstream>
#include "Map.h"
#include "Collider.h"

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

private:
	Factory();
	void createMaps();
	void createDoors();
	void createNPCs();

	static unordered_map<string, unique_ptr<Map>> m_maps;	// maps
	ifstream m_file;
};

