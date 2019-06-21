#include "Character.h"
#include "Map.h"
#include <array>

using std::array;

const float MOVE_SPEED = 2.5f;	// character move speed
const int BOUNDS = 8;			// number of bounds

Character::Character()
{
	// initialize members
	m_moveSpeed = MOVE_SPEED;
	m_direction = Vector2f(0, m_moveSpeed);
}

Character::~Character()
{
}

void Character::draw(RenderWindow & window)
{
	window.draw(m_sprite);
}

FloatRect Character::getGlobalBounds() const
{
	// reduce the bounds of the character to make it collide only from half of his body
	auto bounds = m_sprite.getGlobalBounds();
	bounds.top += (bounds.height / 2.60f);
	bounds.height -= (bounds.height / 2.60f);
	return bounds;
}

void Character::setMap(const Map * map)
{
	m_mapData = map->getMapData();	// get the map collision data
}

void Character::move(bool & inGrass)
{
	m_sprite.move(m_direction);		// move character
	if (checkMapCollision(inGrass))	// if collided with static object in map
		stop();						// stop moving
}

void Character::stop()
{
	m_sprite.move(-m_direction);
}

bool Character::checkMapCollision(bool & inGrass) const
{
	// to check collision with static objects in the map, we save 8 points of the character bounds:
	array<Vector2f, BOUNDS> bounds;
	int index = 0;
	bounds[index++] = m_sprite.getPosition() + Vector2f(0, sizeY / 2);	// top left
	bounds[index++] = bounds[0] + Vector2f(sizeX / 2, 0);	// top middle
	bounds[index++] = bounds[0] + Vector2f(sizeX, 0);		// top right
	bounds[index++] = bounds[0] + Vector2f(0, sizeY / 4);	// left middle
	bounds[index++] = bounds[0] + Vector2f(0, sizeY / 2);	// bottom left
	bounds[index++] = bounds[2] + Vector2f(0, sizeY / 4);	// right middle
	bounds[index++] = bounds[4] + Vector2f(sizeX / 2, 0);	// bottom middle
	bounds[index++] = bounds[4] + Vector2f(sizeX, 0);		// bottom right

	try
	{
		for (auto& bound : bounds)	// for each bound of the character
		{
			// save the data that in the current collided: bound <-> map
			short data = (*m_mapData).at(size_t(bound.y)).at(size_t(bound.x));
			if (data == B_GRASS)	// if collided with grass
				inGrass = true;
			else if (data == B_COLLISION)	// if collided with static object
				return B_COLLISION;
		}
	}
	catch (const std::out_of_range&)	// when going out of the range of the map
	{
		return B_COLLISION;		// return collision
	}
	return B_NO_COLLISION;	// if any of the bounds didn't collide, return no collision
}

void Character::setTextureRect(const IntRect & rect)
{
	m_sprite.setTextureRect(rect);
}
