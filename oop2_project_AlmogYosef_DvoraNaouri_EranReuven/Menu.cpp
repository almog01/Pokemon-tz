#include "Menu.h"

using sf::Vector2f;
using sf::Keyboard;

const int NUM_OF_SELECTIONS = 7;
const unsigned TEXT_SIZE = 20U;
const float TEXT_MARGIN = 20.f;
const float ARROW_MARGIN = 10.f;

Menu::Menu() : m_selection(POKEDEX)
{
	// initialize menu frame
	m_sprite.setTexture(Resource::texture("menu"), true);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	
	// initialize text
	m_text.setFont(Resource::font);
	m_text.setCharacterSize(TEXT_SIZE);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString("POKeDEX\nPOKeMON\nBAG\nProfile\nSAVE\nOPTION\nEXIT");

	// initialize selection arrow
	m_arrow.setTexture(Resource::texture("arrow"), true);
}


Menu::~Menu()
{
}

void Menu::draw(RenderWindow & window)
{
	auto view = window.getView();
	m_sprite.setPosition(Vector2f(view.getCenter().x + (view.getSize().x / 2.f) - (m_sprite.getGlobalBounds().width / 2.f), view.getCenter().y));
	m_text.setPosition(Vector2f(m_sprite.getGlobalBounds().left + TEXT_MARGIN, m_sprite.getGlobalBounds().top));
	m_arrow.setPosition(Vector2f(m_text.getPosition()) + Vector2f(-ARROW_MARGIN, ARROW_MARGIN) + Vector2f(0, m_selection * 18.f));
	Screen::draw(window);
	window.draw(m_text);
	window.draw(m_arrow);
}

void Menu::keyReleasedHandler(const Event & event)
{
	switch (event.key.code)
	{
	case Keyboard::X:			// x pressed
	case Keyboard::Enter:		// or enter pressed
		m_closeScreen = true;
		break;
	case Keyboard::Up:
		m_selection = (SELECTION)((m_selection - 1 < 0) ? m_selection + NUM_OF_SELECTIONS - 1 : m_selection - 1);
		break;
	case Keyboard::Down:
		m_selection = (SELECTION)((m_selection + 1) % NUM_OF_SELECTIONS);
		break;
	}
}
