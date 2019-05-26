#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "Settings.h"
//#include "Player.h"
//#include "NPC.h"
//#include "Map.h"

using sf::RenderWindow;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void draw(RenderWindow & window) = 0;

	/*virtual void handleCollision(GameObject & obj) = 0;
	virtual void handleCollision(Player & player) = 0;
	virtual void handleCollision(NPC & npc) = 0;
	virtual void handleCollision(Map & map) = 0;*/

};

