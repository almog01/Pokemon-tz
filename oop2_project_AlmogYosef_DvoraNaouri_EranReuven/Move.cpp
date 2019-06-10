#include "Move.h"



Move::Move()
{
	//m_moves.resize(7);
	//m_moves[TACKLE] = std::make_unique<Move>("tackle", Element::NORMAL, 30, 30);
	//m_moves[THUNDER] = std::make_unique<Move>("thunder", Element::ELECTRIC, 40, 20);
	//m_moves[FLAMETHROWER] = std::make_unique<Move>("flamethrower", Element::FIRE, 50, 10);
	//m_moves[FLY] = std::make_unique<Move>("fly", Element::FLYING, 40, 10);
	//m_moves[TAIL_WHIP] = std::make_unique<Move>("tail whip", Element::NORMAL, 0, 100);
	//m_moves[ROAR] = std::make_unique<Move>("roar", Element::NORMAL, 0, 30);
	//m_moves[NONE] = std::make_unique<Move>("-", Element::NORMAL, 30, 0);
}

Element Move::stringToElement(const string & x)
{
	if (x == "N_A")
		return N_A;
	else if (x == "ELECTRIC")
		return ELECTRIC;
	else if (x == "GROUND")
		return GROUND;
	else if (x == "FIRE")
		return FIRE;
	else if (x == "WATER")
		return WATER;
	else if (x == "FLYING")
		return FLYING;
	else if (x == "GRASS")
		return GRASS;
	else if (x == "NORMAL")
		return NORMAL;
	else
		return N_A;
}



Move::~Move()
{
}

void Move::draw(RenderWindow & window)
{
}
