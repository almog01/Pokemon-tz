#pragma once
#include "Character.h"
#include "Move.h"

enum xyzPokemon{pikachu, charmander, bulbasaur, squirtle};


class Move;

class Pokemon : public Character
{
public:
	Pokemon(string pokemon);

	void setTextureRect(const IntRect & rect);
	void pokemonLoader(xyzPokemon pokemon);

	// Inherited via Character
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Pokemon & pokemon) override;
	virtual void handleCollision(Door & door) override;

	~Pokemon();

private:
	sf::Sprite m_front;
	sf::Sprite m_back;
	vector<std::unique_ptr<Move>> m_moves;

};

