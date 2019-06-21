#pragma once
#include "GameObject.h"

class Player;
class NPC;
class Pokemon;
class Door;
class ExitDoor;

using sf::Vector2f;
using sf::IntRect;
using sf::FloatRect;

class Collider : public GameObject
{
public:
	Collider();
	virtual ~Collider();

	virtual void setPosition(const Vector2f & pos) = 0;

	virtual void setTextureRect(const IntRect & rect) = 0;

	// Returns the bounding rectangle that blocks the object
	virtual FloatRect getGlobalBounds() const = 0;

	virtual void handleCollision(Collider & collider) = 0;
	virtual void handleCollision(Player & player) = 0;
	virtual void handleCollision(NPC & npc) = 0;
	virtual void handleCollision(Door & door) = 0;
};

