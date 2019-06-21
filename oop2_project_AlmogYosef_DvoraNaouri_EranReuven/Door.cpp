#include "Door.h"
#include "Player.h"


Door::Door(const Vector2f & size, const string & dest, const Vector2f & destPos)
	: m_destination(dest), m_destPos(destPos)
{
	// initialize bounds
	m_bounds.setSize(size);
}


Door::~Door()
{
}

void Door::draw(RenderWindow & window)
{
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
	player.handleCollision(*this);	// call the player's handleCollision
}

void Door::handleCollision(NPC & npc)
{
}

void Door::handleCollision(Door & door)
{
}

