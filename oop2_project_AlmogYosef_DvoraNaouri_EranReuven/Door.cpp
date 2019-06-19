#include "Door.h"
#include "Player.h"


Door::Door(const Vector2f & size, const string & dest, const Vector2f & destPos)
	: m_destination(dest), m_destPos(destPos)
{
	m_bounds.setSize(size);
	m_bounds.setFillColor(sf::Color::Transparent);
}


Door::~Door()
{
}

void Door::draw(RenderWindow & window)
{
	window.draw(m_bounds);
}

void Door::setTextureRect(const IntRect & rect)
{
}

void Door::handleCollision(Collider & collider)
{
	collider.handleCollision(*this);
}

void Door::handleCollision(Player & player)
{
	player.handleCollision(*this);
}

void Door::handleCollision(NPC & npc)
{
}

void Door::handleCollision(Pokemon & pokemon)
{
}

void Door::handleCollision(Door & door)
{
}

