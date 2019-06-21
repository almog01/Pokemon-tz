#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Player.h"
#include "Pokemon.h"
#include <memory>
#include <string>

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::vector;
using sf::Texture;
using sf::Sprite;
using sf::Uint32;
using sf::Vector2f;
using sf::FloatRect;

// Colors of the map data by their int number
enum MapDataColors { C_BLACK = 255, C_WHITE = 4294967295, C_GREEN = 16711935, C_RED = 4278190335 };
// Possible behaviors for map data
enum MapDataBehavior { B_NO_COLLISION = 0, B_COLLISION = 1, B_GRASS = 2 };

class Map : public GameObject
{
public:
	Map(const string & name);	// c-tor
	~Map();						// d-tor

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;

	// Getters
	string getName() const { return m_name; }
	const vector<vector<unsigned short>> * getMapData() const { return &m_mapData; }

	// adds a collider to the map
	void addCollider(unique_ptr<Collider> collider, int index);

	// checks the collision between the player and the colliders in the map (for double dispatch)
	void checkCollision(Player & player);

	// checks the collision of the player's point of view, with npcs in the map, to try chat with them
	bool tryChat(const FloatRect & pov, NPC *& npc) const;

	// adds a wild pokemon to the map vector, so the player will interact with them when walking in grass
	void addWildPokemon(const Pokemon & pokemon) { m_wildPokemons.emplace_back(make_shared<Pokemon>(pokemon)); }
	
	// returns randomly generated pokemon which the map is holding
	Pokemon getWildPokemon() const;

private:
	// loads the map
	void loadMap(const string & name);
	// loads the map data
	void loadMapData(const string & name);

	// returns the unsigned short data, for each color
	unsigned short getColorData(Uint32 color, unsigned x, unsigned y);

	string m_name;		// map name
	Sprite m_sprite;	// map sprite
	vector<vector<unsigned short>> m_mapData;		// map collision data matrix
	vector<unique_ptr<Vector2f>> m_collidersPos;	// vector to save the positions for each collider in the map
	vector<unique_ptr<Collider>> m_colliders;		// vector to save the colliders in the map
	vector<shared_ptr<Pokemon>> m_wildPokemons;		// vector to save the wild pokemons which can be found in the map grass
};

