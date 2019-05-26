#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();

	virtual void update() override;

	// Inherited via Character
	/*virtual void handleCollision(GameObject & obj) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Map & map) override;*/
};

