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

enum MapDataColors { C_BLACK = 255, C_WHITE = 4294967295, C_GREEN = 16711935, C_RED = 4278190335 };
enum MapDataBehavior { B_NO_COLLISION = 0, B_COLLISION = 1, B_GRASS = 2 };

class Map : public GameObject
{
public:
	Map(const string & name);
	~Map();

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;

	// Getters
	string getName() const { return m_name; }
	const vector<vector<unsigned short>> * getMapData() const { return &m_mapData; }

	void addCollider(unique_ptr<Collider> collider, int index);

	void checkCollision(Player & player);

	bool tryChat(const FloatRect & pov, NPC *& npc) const;

	void addWildPokemon(const Pokemon & pokemon) { m_wildPokemons.emplace_back(make_shared<Pokemon>(pokemon)); }

private:
	void loadMap(string name);

	void loadMapData(string name);

	unsigned short getColorData(Uint32 color, unsigned x, unsigned y);

	string m_name;
	//Sprite m_SpriteTop;
	Sprite m_SpriteBottom;
	vector<vector<unsigned short>> m_mapData;
	vector<unique_ptr<Vector2f>> m_collidersPos;
	vector<unique_ptr<Collider>> m_colliders;
	vector<shared_ptr<Pokemon>> m_wildPokemons;
};

