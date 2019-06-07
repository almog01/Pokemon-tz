#pragma once
#include "Character.h"

using std::string;

class NPC : public Character
{
public:
	NPC(const string & name);
	~NPC();

	// Inherited via Character
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Pokemon & pokemon) override;
	virtual void handleCollision(Door & door) override;
};

