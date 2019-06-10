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
enum Moves {
	TACKLE,
	THUNDER,
	FLAMETHROWER,
	FLY,
	TAIL_WHIP,
	ROAR,
	NONE
};

class Move
{
public:
	Move();
	Move(string name, Element element, int dmg, int spd);

	~Move();

private:
	string m_name;
	Element m_element;
	int m_damage;
	int m_speed;

	std::vector<std::unique_ptr<Move>> m_moves;

};

