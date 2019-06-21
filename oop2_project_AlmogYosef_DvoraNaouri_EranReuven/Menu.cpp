#include "Menu.h"

using sf::Vector2f;
using sf::Color;
using sf::Keyboard;

/*constants for the menu settings*/
const unsigned TEXT_SIZE = 18U;
const float TEXT_MARGIN_X = 30.f;
const float TEXT_MARGIN_Y = 18.f;
const float ARROW_MARGIN = 8.f;

//constructor init menu size, if it exitable, and the arrow texture (default is the black arrow)
Menu::Menu(const Texture & texture, const Vector2f & size, bool exitable, const Texture & arrow)
	: m_size(size), m_exitable(exitable), m_curSelection(0, 0), m_textPos(0, 0)
{
	//setting the texts of the menu
	m_textSize = TEXT_SIZE;
	m_textMarginX = TEXT_MARGIN_X;
	m_textMarginY = TEXT_MARGIN_Y;

	// initialize screen
	m_screen.setTexture(texture);

	// initialize selection arrow
	m_arrow.setTexture(arrow, true);
}

Menu::~Menu() //destructor
{
}

void Menu::select() //select functions for the menu
{
	int selected = int((m_curSelection.y * m_size.x) + m_curSelection.x); //get the selection
	if (m_commands[selected].second)	// if the command is not nullptr
		m_commands[selected].second->execute(); //execute the selection command
}

void Menu::draw(RenderWindow & window) //draw function
{
	window.draw(m_screen);  //draw the menu screen
	for (auto & text : m_texts) //loop to draw the texts via iterator
		window.draw(text);
	if (!m_texts.empty()) //if the texts isnt empty
	{
		int selected = int((m_curSelection.y * m_size.x) + m_curSelection.x); //get the selection 
		m_arrow.setPosition(Vector2f(m_texts[selected].getPosition()) + Vector2f(-ARROW_MARGIN + 1.f, ARROW_MARGIN)); //change the arrow position
		window.draw(m_arrow); //draw the arrow
	}
}

void Menu::keyReleasedHandler(const Event & event)
{
	switch (event.key.code)
	{
	case Keyboard::Up: //up button pressed
		m_curSelection.y = (m_curSelection.y - 1 >= 0) ? m_curSelection.y - 1 : m_size.y - 1;
		break;
	case Keyboard::Down: //down button pressed
		m_curSelection.y = (m_curSelection.y + 1 < m_size.y) ? m_curSelection.y + 1 : 0;
		break;
	case Keyboard::Left: //left button pressed
		m_curSelection.x = (m_curSelection.x - 1 >= 0) ? m_curSelection.x - 1 : m_size.x - 1;
		break;
	case Keyboard::Right: //right button pressed
		m_curSelection.x = (m_curSelection.x + 1 < m_size.x) ? m_curSelection.x + 1 : 0;
		break;
	case Keyboard::Z:		// z pressed
		select();
		break;
	case Keyboard::X:		// x pressed
		if (m_exitable) 
			deactivate(); //deactivate
		break;
	}
}

void Menu::addCommand(const string & name, unique_ptr<Command> c) //add command function
{
	// initialize text
	Text text(name, Resource::font, m_textSize); 
	text.setFillColor(Color::Black);
	m_texts.push_back(text);

	//inserting the command into the commands vector
	m_commands.emplace_back(option(name, std::move(c)));
}

void Menu::setPosition(const Vector2f & pos) //set position function
{
	m_screen.setPosition(pos); //set the menu position
	if (!m_texts.empty())
	{	// first text position
		m_texts[0].setPosition(Vector2f(m_screen.getGlobalBounds().left + 14.f, m_screen.getGlobalBounds().top + 2.f));
		m_textPos.x++;

		for (size_t i = 1; i < m_texts.size(); ++i) //loop to run over the texts
		{											//and changed their positions according the menu screen
			if (m_textPos.x < m_size.x)
			{
				m_texts[i].setPosition(m_texts[0].getPosition() + Vector2f(m_textMarginX * (m_textPos.x + 1), m_textMarginY * m_textPos.y));
				m_textPos.x++;
			}
			else if (m_textPos.x >= m_size.x)
			{
				m_textPos.x = 1;
				m_textPos.y++;
				m_texts[i].setPosition(m_texts[0].getPosition() + Vector2f(0, m_textMarginY * m_textPos.y));
			}
		}
	}
}