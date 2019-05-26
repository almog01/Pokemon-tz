#pragma once
#include "Character.h"
class NPC : public Character
{
public:
	NPC();
	~NPC();

	// Inherited via Character
	/*virtual void handleCollision(GameObject & obj) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Map & map) override;*/
};

