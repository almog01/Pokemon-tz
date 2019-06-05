#include "Map.h"
#include <Windows.h>

using sf::Image;
using sf::Vector2u;
using std::make_unique;

Map::Map(const string & name) : m_name(name)
{
	loadMap(name);
}


Map::~Map()
{
}

void Map::loadMap(string name)
{
	// Init sprite
	m_SpriteBottom.setTexture(Resource::texture(name));
	loadMapData(name);
}

void Map::draw(RenderWindow & window)
{
	window.draw(m_SpriteBottom);
	for (auto& collider : m_colliders)
		collider->draw(window);
}

void Map::loadMapData(string name)
{
	Image image(Resource::image(name + "_data"));

	//Create data map
	Vector2u size = image.getSize();

	for (unsigned y = 0; y < size.y; y++)
	{
		vector<unsigned short> row;
		for (unsigned x = 0; x < size.x; x++)
		{
			sf::Color pixel = image.getPixel(x, y);
			row.push_back(getColorData(pixel.toInteger(), x, y));
		}
		m_mapData.push_back(row);
	}
}

unsigned short Map::getColorData(Uint32 color, unsigned x, unsigned y)
{
	switch (color)
	{
	case 255:			// black = collision
		return 1;
	case 4294967295:	// white = no collision
		return 0;
	case 16711935:		// green = grass
		return 2;
	case 4278190335:	// red = collider
		m_collidersPos.emplace_back(make_unique<Vector2f>(float(x), float(y)));
		return 0;
	default:
		return 0;		// no collision
	}
}

void Map::addCollider(unique_ptr<Collider> collider)
{
	static int index = 0;
	collider->setPosition(*(m_collidersPos)[index]);
	m_colliders.emplace_back(std::move(collider));
	index++;
}

void Map::checkCollision(Player & player)
{
	for (auto it1 = m_colliders.begin(); it1 != m_colliders.end(); ++it1)
	{
		if ((*it1)->getGlobalBounds().intersects(player.getGlobalBounds()))
			(*it1)->handleCollision(player);
	}
}