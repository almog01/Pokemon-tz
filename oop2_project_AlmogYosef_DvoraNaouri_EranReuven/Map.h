#pragma once
#include "GameObject.h"
#include <string>

using std::string;
using std::vector;
using sf::Texture;
using sf::Sprite;
using sf::Uint32;

class Map : public GameObject
{
public:
	Map();
	virtual ~Map();

	void loadMap(string name);

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;

	const vector<vector<unsigned short>> & getMapData() const { return m_mapData; }

	// Inherited via GameObject
	/*virtual void handleCollision(GameObject & obj) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Map & map) override;*/

private:
	void loadMapData(string name);

	unsigned short getColorData(Uint32 color);

	//Texture m_TextureTop;
	//Sprite m_SpriteTop;
	Sprite m_SpriteBottom;
	vector<vector<unsigned short>> m_mapData;

};

