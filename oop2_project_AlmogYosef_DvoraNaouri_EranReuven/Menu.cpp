#include "Menu.h"

using sf::Vector2f;
using sf::Color;
using sf::Keyboard;

const unsigned TEXT_SIZE = 18U;
const float TEXT_MARGIN_X = 30.f;
const float TEXT_MARGIN_Y = 18.f;
const float ARROW_MARGIN = 8.f;

Menu::Menu(const Texture & texture, const Vector2f & size, bool exitable, const Texture & arrow)
	: m_size(size), m_exitable(exitable), m_curSelection(0, 0), m_textPos(0, 0)
{
	m_textSize = TEXT_SIZE;
	m_textMarginX = TEXT_MARGIN_X;
	m_textMarginY = TEXT_MARGIN_Y;
	// initialize screen
	m_screen.setTexture(texture);

	// initialize selection arrow
	m_arrow.setTexture(arrow, true);
}

Menu::~Menu()
{
}

void Menu::select()
{
	int selected = int((m_curSelection.y * m_size.x) + m_curSelection.x);
	if (m_commands[selected].second)	// if the command is not nullptr
		m_commands[selected].second->execute();
}

void Menu::draw(RenderWindow & window)
{
	window.draw(m_screen);
	for (auto & text : m_texts)
		window.draw(text);
	if (!m_texts.empty())
	{
		int selected = int((m_curSelection.y * m_size.x) + m_curSelection.x);
		m_arrow.setPosition(Vector2f(m_texts[selected].getPosition()) + Vector2f(-ARROW_MARGIN + 1.f, ARROW_MARGIN));
		window.draw(m_arrow);
	}
}

void Menu::keyReleasedHandler(const Event & event)
{
	switch (event.key.code)
	{
	case Keyboard::Up:
		m_curSelection.y = (m_curSelection.y - 1 >= 0) ? m_curSelection.y - 1 : m_size.y - 1;
		break;
	case Keyboard::Down:
		m_curSelection.y = (m_curSelection.y + 1 < m_size.y) ? m_curSelection.y + 1 : 0;
		break;
	case Keyboard::Left:
		m_curSelection.x = (m_curSelection.x - 1 >= 0) ? m_curSelection.x - 1 : m_size.x - 1;
		break;
	case Keyboard::Right:
		m_curSelection.x = (m_curSelection.x + 1 < m_size.x) ? m_curSelection.x + 1 : 0;
		break;
	case Keyboard::Z:		// z pressed
		select();
		break;
	case Keyboard::X:		// x pressed
		if (m_exitable)
			deactivate();
		break;
	}
}

void Menu::addCommand(const string & name, unique_ptr<Command> c)
{
	// initialize text
	Text text(name, Resource::font, m_textSize);
	text.setFillColor(Color::Black);
	if (m_texts.empty())
	{	// first text position
		text.setPosition(Vector2f(m_screen.getGlobalBounds().left + 14.f, m_screen.getGlobalBounds().top + 2.f));
		m_textPos.x++;
	}
	else
	{
		if (m_textPos.x < m_size.x)
		{
			text.setPosition(m_texts[0].getPosition() + Vector2f(m_textMarginX * (m_textPos.x + 1), m_textMarginY * m_textPos.y));
			m_textPos.x++;
		}
		else if (m_textPos.x >= m_size.x)
		{
			m_textPos.x = 1;
			m_textPos.y++;
			text.setPosition(m_texts[0].getPosition() + Vector2f(0, m_textMarginY * m_textPos.y));
		}
	}
	m_texts.push_back(text);
	m_commands.emplace_back(option(name, std::move(c)));
}

