#include "Character.h"
#include "Map.h"
#include <array>

using std::array;

const float MOVE_SPEED = 2.5f;
const int BOUNDS = 8;

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
	auto bounds = m_sprite.getGlobalBounds();
	bounds.top += (bounds.height / 2.60f);
	bounds.height -= (bounds.height / 2.60f);
	return bounds;
}

void Character::setMap(const Map * map)
{
	m_mapData = map->getMapData();
}

void Character::move(bool & inGrass)
{
	m_sprite.move(m_direction);
	if (checkMapCollision(inGrass))
		stop();
}

void Character::stop()
{
	m_sprite.move(-m_direction);
}

bool Character::checkMapCollision(bool & inGrass) const
{
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
		for (auto& bound : bounds)
		{
			short data = (*m_mapData).at(size_t(bound.y)).at(size_t(bound.x));
			if (data == B_GRASS)
				inGrass = true;
			else if (data == B_COLLISION)
				return B_COLLISION;
		}
	}
	catch (const std::out_of_range&)
	{
		return B_COLLISION;
	}
	return B_NO_COLLISION;
}

void Character::setTextureRect(const IntRect & rect)
{
	m_sprite.setTextureRect(rect);
}
