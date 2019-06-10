#include "Battle.h"



Battle::Battle(int battleType)
{
	m_sprite.setTexture(Resource::texture("battle"));
	battleArenaLoader(battleType);
}

void Battle::battleArenaLoader(int battleType)
{
	switch (battleType)
	{
	case 1:
	//	window.draw(m_sprite);
	//	window.setView(sf::View(sf::FloatRect(2.f, 22.f, 240.f, 112.f)));
		m_view = sf::View(sf::FloatRect(2.f, 22.f, 240.f, 112.f));
		break;
	}
}

void Battle::draw(RenderWindow & window)
{
	window.draw(m_sprite);
	window.setView(m_view);
	m_pokemons = std::make_unique<Pokemon>("pikachu");
	m_pokemons->setPosition(Vector2f(0, 50));
	m_pokemons->draw(window);
}

Battle::~Battle()
{
}

void Battle::keyReleasedHandler(const Event & event)
{
}
