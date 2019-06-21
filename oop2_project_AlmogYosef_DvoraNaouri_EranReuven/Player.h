#pragma once
#include "Character.h"
#include "Trainer.h"
#include "Animation.h"

class GameManager;
class Map;

using sf::RectangleShape;
using sf::FloatRect;

class Player : public Character, public Trainer
{
public:
	// Singleton Player
	static Player& instance();
	~Player();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	// updates the player
	void update(GameManager & gm);
	
	// Getters
	string getMap() const { return m_map; }
	FloatRect getPov() const { return m_pov.getGlobalBounds(); }

	// Setters
	virtual void setMap(const Map * map) override;

	// Inherited via Character
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Door & door) override;

private:
	Player();	// c-tor

	Animation m_animation;	// animation of the player
	string m_map;			// current map
	RectangleShape m_pov;	// point of view
};

