#pragma once
#include "Screen.h"
#include "Pokemon.h"
class Battle : public Screen
{
public:
	Battle(int battleType = 1);
	void battleArenaLoader(int battleType);
	virtual void draw(RenderWindow & window) override;
	~Battle();
private:
	sf::View m_view;

	// Inherited via Screen
	virtual void keyReleasedHandler(const Event & event) override;

	std::unique_ptr<Pokemon> m_pokemons;
};

