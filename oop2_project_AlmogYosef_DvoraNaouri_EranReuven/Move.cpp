#include "Move.h"



Move::Move()
{
	m_moves.resize(7);
	m_moves[TACKLE] = std::make_unique<Move>("tackle", Element::NORMAL, 30, 30);
	m_moves[THUNDER] = std::make_unique<Move>("thunder", Element::ELECTRIC, 40, 20);
	m_moves[FLAMETHROWER] = std::make_unique<Move>("flamethrower", Element::FIRE, 50, 10);
	m_moves[FLY] = std::make_unique<Move>("fly", Element::FLYING, 40, 10);
	m_moves[TAIL_WHIP] = std::make_unique<Move>("tail whip", Element::NORMAL, 0, 100);
	m_moves[ROAR] = std::make_unique<Move>("roar", Element::NORMAL, 0, 30);
	m_moves[NONE] = std::make_unique<Move>("-", Element::NORMAL, 30, 0);
}

Move::Move(string name, Element element, int dmg, int spd)
	:m_name(name), m_element(element), m_damage(dmg), m_speed(spd)
{

}


Move::~Move()
{
}
