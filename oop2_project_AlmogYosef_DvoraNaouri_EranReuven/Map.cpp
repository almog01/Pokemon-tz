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

void Map::loadMap(const string & name)
{
	// initialize sprite
	m_sprite.setTexture(Resource::texture(name));
	loadMapData(name);
}

void Map::draw(RenderWindow & window)
{
	// draw map and all his colliders
	window.draw(m_sprite);
	for (auto& collider : m_colliders)
		collider->draw(window);
}

void Map::loadMapData(const string & name)
{
	Image image(Resource::image(name + "_data"));	// get the map data image
	Vector2u size = image.getSize();	// map data image size

	// iterate through each pixel in the image (image = matrix of pixels)
	for (unsigned y = 0; y < size.y; y++)
	{
		vector<unsigned short> row;		// create new row
		for (unsigned x = 0; x < size.x; x++)
		{
			sf::Color pixel = image.getPixel(x, y);		// save the (x,y) pixel
			row.push_back(getColorData(pixel.toInteger(), x, y));	// push back the pixel data to the row
		}
		m_mapData.push_back(row);	// add row to the matrix
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
		return B_NO_COLLISION;	// else = no collision
	}
}

void Map::addCollider(unique_ptr<Collider> collider, int index)
{
	// set the collider position, based on the m_collidersPos vector
	collider->setPosition(*(m_collidersPos)[index]);
	// emplace back the new collider
	m_colliders.emplace_back(std::move(collider));
}

void Map::checkCollision(Player & player)
{
	// check collision between each map collider and the player
	for (auto it1 = m_colliders.begin(); it1 != m_colliders.end(); ++it1)
	{
		if ((*it1)->getGlobalBounds().intersects(player.getGlobalBounds()))		// if they intersects
			(*it1)->handleCollision(player);		// call collision handler
	}
}

bool Map::tryChat(const FloatRect & pov, NPC *& npc) const
{
	// check collision between the "point of view" and the map colliders
	for (auto it1 = m_colliders.begin(); it1 != m_colliders.end(); ++it1)
	{
		if ((*it1)->getGlobalBounds().intersects(pov))		// if they intersects
		{
			NPC* npcPtr = dynamic_cast<NPC*>((*it1).get());	// check if the collider is npc
			if (npcPtr)
			{
				npc = npcPtr;
				return true;
			}
		}
	}
	return false;
}

Pokemon Map::getWildPokemon() const
{
	size_t random = rand() % m_wildPokemons.size();		// get random pokemon index
	int level = (rand() % 5) + 2;					// get random level between 2-6
	m_wildPokemons.at(random)->setLevel(level);		// set the pokemon level
	return *m_wildPokemons.at(random);				// and return it
}
