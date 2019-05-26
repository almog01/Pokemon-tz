#include "Character.h"

const float MOVE_SPEED = 5.f;

Character::Character()	
	//: m_moveSpeed(MOVE_SPEED), m_direction(Down), m_moving(false), m_turning(false), m_counter(1)
{
	// initialize members
	m_moveSpeed = MOVE_SPEED;
	m_direction = Vector2f(0, m_moveSpeed);
	m_sprite.setScale(Settings::SCALE(), Settings::SCALE());
	/*m_counter = 0;
	m_moving = false;
	m_turning = false;
	m_moveCounter = 0;
	m_moveState = 1;*/
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
	/*m_lastPos = getPosition();
	if (m_moving)
		move();*/
}

void Character::move()
{
	m_sprite.move(m_direction);
	if (checkCollision())
		stop();
	//m_sprite.setTextureRect(sf::IntRect((1 - m_counter) * sizeX, getDirectionIndex(m_direction) * sizeY, sizeX, sizeY));
	
	//m_moveSpeed = Settings::BASE() / Settings::GAME_SPEED() * Settings::SCALE();

	//if (!m_turning)
	//{
	//switch (m_direction)
	//{
	//case Down:
	//	m_sprite.move({ 0, m_moveSpeed});	// down = {0, y}	
	//	break;
	//case Up:
	//	m_sprite.move({ 0, -m_moveSpeed});	// up = {0, -y}
	//	break;
	//case Right:
	//	m_sprite.move({ m_moveSpeed, 0 });	// right = {x, 0}
	//	break;
	//case Left:
	//	m_sprite.move({ -m_moveSpeed, 0 });	// left = {-x, 0}
	//	break;
	//default:
	//	break;
	//}
	//}

	//m_moveCounter += (Settings::BASE() / Settings::GAME_SPEED());
	//if (m_moveCounter >= Settings::BASE()) {
	//	// Reset sprite to stop view
	//	m_counter = 0;
	//	m_sprite.setTextureRect(sf::IntRect((1 - m_counter) * sizeX, getDirectionIndex(m_direction) * sizeY, sizeX, sizeY));

	//	m_moving = false;
	//}
}

void Character::stop()
{
	m_sprite.move(-m_direction);
}

bool Character::checkCollision() const
{
	int coeff = Settings::SCALE() * Settings::BASE();

	Vector2f topLeft = m_sprite.getPosition();
	Vector2f topRight = topLeft + Vector2f(float(Settings::BASE() * Settings::SCALE()), 0);
	Vector2f bottomLeft = topLeft + Vector2f(0, float(Settings::BASE() * Settings::SCALE()));
	Vector2f bottomRight = bottomLeft + Vector2f(float(Settings::BASE() * Settings::SCALE()), 0);
	unsigned int x1 = (unsigned int)(topLeft.x / coeff);
	unsigned int y1 = (unsigned int)(topLeft.y / coeff);
	unsigned int x2 = (unsigned int)(topRight.x / coeff);
	unsigned int y2 = (unsigned int)(topRight.y / coeff);
	unsigned int x3 = (unsigned int)(bottomLeft.x / coeff);
	unsigned int y3 = (unsigned int)(bottomLeft.y / coeff);
	unsigned int x4 = (unsigned int)(bottomRight.x / coeff);
	unsigned int y4 = (unsigned int)(bottomRight.y / coeff);

	return (m_mapData[y1][x1] == 1 || m_mapData[y2][x2] == 1 || m_mapData[y3][x3] == 1 || m_mapData[y4][x4] == 1);
}

int Character::getDirectionIndex(Direction dir)
{
	switch (dir) {
	case Down:
		return 0;
	case Up:
		return 1;
	case Right:
		return 2;
	case Left:
		return 3;
	default:
		return 0;
	}
}

void Character::startMove(Direction dir)
{
	/*if (dir != m_direction)
	{
		m_turning = true;
		m_counter = 0;
	}
	else
	{
		m_turning = false;
		m_counter = m_moveState;
	}
	m_turning = dir != m_direction;

	m_moveCounter = 0;
	m_direction = dir;

	m_moving = true;
	m_moveState *= -1;*/
}
