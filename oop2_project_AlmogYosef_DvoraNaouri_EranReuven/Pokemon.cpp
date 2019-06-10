#include "Pokemon.h"



Pokemon::Pokemon(string pokemon)
{
	m_sprite.setTexture(Resource::texture(pokemon), true);
	//m_moves.resize(7);
	//m_moves[0] = std::make_unique<Move>("tackle", Element::NORMAL, 30, 30);
	//m_moves[1] = std::make_unique<Move>("thunder", Element::ELECTRIC, 40, 20);
	//m_moves[2] = std::make_unique<Move>("flamethrower", Element::FIRE, 50, 10);
	//m_moves[3] = std::make_unique<Move>("fly", Element::FLYING, 40, 10);
	//m_moves[4] = std::make_unique<Move>("tail whip", Element::NORMAL, 0, 100);
	//m_moves[5] = std::make_unique<Move>("roar", Element::NORMAL, 0, 30);
	//m_moves[6] = std::make_unique<Move>("-", Element::NORMAL, 30, 0);
	//
}


void Pokemon::setTextureRect(const IntRect & rect)
{
	m_sprite.setTextureRect(rect);
}

void Pokemon::pokemonLoader(xyzPokemon pokemon)
{
	switch (pokemon)
	{
	default:
		break;
	}
}

void Pokemon::handleCollision(Collider & collider)
{
}

void Pokemon::handleCollision(Player & player)
{
}

void Pokemon::handleCollision(NPC & npc)
{
}

void Pokemon::handleCollision(Pokemon & pokemon)
{
}

void Pokemon::handleCollision(Door & door)
{
}

Pokemon::~Pokemon()
{
}
