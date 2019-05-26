#include "Map.h"
#include <Windows.h>

using sf::Image;

Map::Map()
{
}


Map::~Map()
{
}

void Map::loadMap(string name)
{
	// Init sprite
	m_SpriteBottom.setTexture(Resource::texture("vermillion"));
	m_SpriteBottom.setScale(Settings::SCALE(), Settings::SCALE());

	loadMapData(name);
}

void Map::draw(RenderWindow & window)
{
	window.draw(m_SpriteBottom);
}

void Map::loadMapData(string name)
{
	Image image(Resource::image("vermillion_data"));

	//Create data map
	sf::Vector2u size = image.getSize();
	for (unsigned y = 0; y < size.y; y += 16)
	{
		vector<unsigned short> row;
		for (unsigned x = 0; x < size.x; x += 16)
		{
			sf::Color pixel = image.getPixel(x, y);
			row.push_back(getColorData(pixel.toInteger()));
		}
		m_mapData.push_back(row);
	}
}

unsigned short Map::getColorData(Uint32 color)
{
	switch (color)
	{
	case 255:
		return 1;		// collision
	default:
		return 0;		// no collision
	}
}

//void Map::handleCollision(GameObject & obj)
//{
//}
//
//void Map::handleCollision(Player & player)
//{
//}
//
//void Map::handleCollision(NPC & npc)
//{
//}
//
//void Map::handleCollision(Map & map)
//{
//}
