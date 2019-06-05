#pragma once
#include "Character.h"
#include "Animation.h"

class Map;

class Player : public Character
{
public:
	Player();
	~Player();

	virtual void update() override;

	virtual void setMap(const Map * map) override;
	string getMap() { return m_map; }

	// Inherited via Character
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Pokemon & pokemon) override;
	virtual void handleCollision(Door & door) override;

private:
	Animation m_animation;
	string m_map;	// current map
};

