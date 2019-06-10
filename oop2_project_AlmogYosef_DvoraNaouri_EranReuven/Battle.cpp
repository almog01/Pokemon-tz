#include "Battle.h"
#include "Factory.h"


Battle::Battle(int battleType)
{
	m_sprite.setTexture(Resource::texture("battle"));
	battleArenaLoader(battleType);
	m_p1 = std::make_unique<Pokemon>(Factory::pokemon("pikachu"));
	m_p1->setTexture("back");
	m_p2 = std::make_unique<Pokemon>(Factory::pokemon("pikachu"));
	m_p2->setTexture("front");
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
	auto view = window.getView();
	m_p1->setPosition(Vector2f(view.getCenter().x, view.getCenter().y));
	m_p2->setPosition(Vector2f(view.getCenter().x, view.getCenter().y));
	m_p1->draw(window);
	m_p2->draw(window);

	//m_pokemons = std::make_unique<Pokemon>("pikachu");
	//m_pokemons->setPosition(Vector2f(0, 50));
	//m_pokemons->draw(window);
}

Battle::~Battle()
{
}

void Battle::keyReleasedHandler(const Event & event)
{
}
