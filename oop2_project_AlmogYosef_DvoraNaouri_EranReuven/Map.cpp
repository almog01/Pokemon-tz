#include "Map.h"
#include "NPC.h"

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
	case C_BLACK:				// black = collision
		return B_COLLISION;
	case C_WHITE:				// white = no collision
		return B_NO_COLLISION;
	case C_GREEN:				// green = grass
		return B_GRASS;
	case C_RED:					// red = save collider position
		m_collidersPos.emplace_back(make_unique<Vector2f>(float(x), float(y)));
		return B_NO_COLLISION;
	default:
		return B_NO_COLLISION;	// no collision
	}
}

void Map::addCollider(unique_ptr<Collider> collider, int index)
{
	collider->setPosition(*(m_collidersPos)[index]);
	m_colliders.emplace_back(std::move(collider));
}

void Map::checkCollision(Player & player)
{
	for (auto it1 = m_colliders.begin(); it1 != m_colliders.end(); ++it1)
	{
		if ((*it1)->getGlobalBounds().intersects(player.getGlobalBounds()))
			(*it1)->handleCollision(player);
	}
}

bool Map::tryChat(const FloatRect & pov, NPC *& npc) const
{
	for (auto it1 = m_colliders.begin(); it1 != m_colliders.end(); ++it1)
	{
		if ((*it1)->getGlobalBounds().intersects(pov))
		{
			NPC* npcPtr = dynamic_cast<NPC*>((*it1).get());
			if (npcPtr)
			{
				npc = npcPtr;
				return true;
			}
		}
	}
	return false;
}
