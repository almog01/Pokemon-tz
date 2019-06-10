#pragma once
#include "GameObject.h"

enum Element {
	N_A, // Not applicable
	ELECTRIC,
	GROUND,
	FIRE,
	WATER,
	FLYING,
	GRASS,
	NORMAL
};

class Move : public GameObject
{
public:
	Move();
	Move(const Move&) = default;

	static Element stringToElement(const string & x);

	//set and get function for move members
	void setElement(Element element) { m_element = element; }
	Element getElement() { return m_element; }
	void setDmg(int dmg) { m_damage = dmg; }
	int getDmg() { return m_damage; }
	void setSpeed(int speed) { m_speed = speed; }
	int getSpeed() { return m_speed; }

	~Move();

private:
	Element m_element;
	int m_damage;
	int m_speed;

	//std::vector<std::unique_ptr<Move>> m_moves;

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;
};

