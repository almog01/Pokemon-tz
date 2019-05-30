#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "Settings.h"

using sf::RenderWindow;
using sf::IntRect;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void draw(RenderWindow & window) = 0;

	virtual void setTextureRect(const IntRect & rect) = 0;
	/*virtual void handleCollision(GameObject & obj) = 0;
	virtual void handleCollision(Player & player) = 0;
	virtual void handleCollision(NPC & npc) = 0;
	virtual void handleCollision(Map & map) = 0;*/

};

