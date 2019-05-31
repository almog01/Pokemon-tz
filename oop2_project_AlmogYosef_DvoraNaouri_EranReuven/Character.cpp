#include "Character.h"

const float MOVE_SPEED = 2.5f;

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

void Character::update()
{
}

void Character::move()
{
	m_sprite.move(m_direction);
	if (checkMapCollision())
		stop();
}

void Character::stop()
{
	m_sprite.move(-m_direction);
}

bool Character::checkMapCollision() const
{
	Vector2f topLeft = m_sprite.getPosition() + Vector2f(0, sizeY / 2);
	Vector2f topMiddle = topLeft + Vector2f(sizeX / 2, 0);
	Vector2f topRight = topLeft + Vector2f(sizeX, 0);
	Vector2f LeftMiddle = topLeft + Vector2f(0, sizeY / 4);
	Vector2f RightMiddle = topRight + Vector2f(0, sizeY / 4);
	Vector2f bottomLeft = topLeft + Vector2f(0, sizeY / 2);
	Vector2f bottomMiddle = bottomLeft + Vector2f(sizeX / 2, 0);
	Vector2f bottomRight = bottomLeft + Vector2f(sizeX, 0);
	unsigned int x1 = (unsigned int)(topLeft.x);
	unsigned int y1 = (unsigned int)(topLeft.y);
	unsigned int x2 = (unsigned int)(topMiddle.x);
	unsigned int y2 = (unsigned int)(topMiddle.y);
	unsigned int x3 = (unsigned int)(topRight.x);
	unsigned int y3 = (unsigned int)(topRight.y);
	unsigned int x4 = (unsigned int)(LeftMiddle.x);
	unsigned int y4 = (unsigned int)(LeftMiddle.y);
	unsigned int x5 = (unsigned int)(RightMiddle.x);
	unsigned int y5 = (unsigned int)(RightMiddle.y);
	unsigned int x6 = (unsigned int)(bottomLeft.x);
	unsigned int y6 = (unsigned int)(bottomLeft.y);
	unsigned int x7 = (unsigned int)(bottomMiddle.x);
	unsigned int y7 = (unsigned int)(bottomMiddle.y);
	unsigned int x8 = (unsigned int)(bottomRight.x);
	unsigned int y8 = (unsigned int)(bottomRight.y);

	return ((*m_mapData)[y1][x1] == 1 || (*m_mapData)[y2][x2] == 1 || (*m_mapData)[y3][x3] == 1 || (*m_mapData)[y4][x4] == 1 ||
			(*m_mapData)[y5][x5] == 1 || (*m_mapData)[y6][x6] == 1 || (*m_mapData)[y7][x7] == 1 || (*m_mapData)[y8][x8] == 1);
}

void Character::setTextureRect(const IntRect & rect)
{
	m_sprite.setTextureRect(rect);
}
