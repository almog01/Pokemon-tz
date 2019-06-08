#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Player.h"
#include <memory>
#include <string>

using std::unique_ptr;
using std::string;
using std::vector;
using sf::Texture;
using sf::Sprite;
using sf::Uint32;
using sf::Vector2f;
using sf::FloatRect;

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
};

