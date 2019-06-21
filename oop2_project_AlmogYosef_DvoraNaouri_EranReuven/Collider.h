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
	Collider() = default;			// c-tor
	virtual ~Collider() = default;	// d-tor

	// sets the collider position
	virtual void setPosition(const Vector2f & pos) = 0;

	// sets the collider's texture rect
	virtual void setTextureRect(const IntRect & rect) = 0;

	// returns the bounding rectangle that blocks the object
	virtual FloatRect getGlobalBounds() const = 0;

	// double dispatch for each type of objects that can collide
	virtual void handleCollision(Collider & collider) = 0;
	virtual void handleCollision(Player & player) = 0;
	virtual void handleCollision(NPC & npc) = 0;
	virtual void handleCollision(Door & door) = 0;
};

