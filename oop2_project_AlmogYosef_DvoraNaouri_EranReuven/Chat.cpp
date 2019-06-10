#include "Chat.h"
#include <sstream>

using sf::Vector2f;
using sf::VideoMode;
using sf::Keyboard;
using std::istringstream;

const unsigned TEXT_SIZE = 15U;
const float TEXT_MARGIN = 11.f;
const float MARGIN_TOP = 4.f;
const size_t MAX_LINE = 39;

Chat::Chat(const RenderWindow & window, const string & chat)
{
	// initialize chat window
	m_sprite.setTexture(Resource::texture("chat_window"), true);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	auto view = window.getView();
	m_sprite.setPosition(Vector2f(view.getCenter().x, view.getCenter().y + (view.getSize().y / 2.5f)));

	// initialize text
	m_text.setFont(Resource::font);
	m_text.setCharacterSize(TEXT_SIZE);
	m_text.setFillColor(sf::Color::Black);
	auto windowBounds = m_sprite.getGlobalBounds();
	m_text.setPosition(Vector2f(windowBounds.left + TEXT_MARGIN, windowBounds.top + MARGIN_TOP));
	
	// set chat
	setChat(chat);
}


Chat::~Chat()
{
}

void Chat::draw(RenderWindow & window)
{
	Screen::draw(window);
	window.draw(m_text);
}

void Chat::setChat(const string & text)
{
	istringstream iss(text);
	string word;
	string line;
	string sentence;
	int counter = 0;

	while (iss >> word)
	{
		if (counter % 2 == 0)
		{
			if (line.length() + word.length() > MAX_LINE)
			{
				sentence += line;
				sentence += '\n';
				line.clear();
				line += word;
				counter++;
			}
			else
				line += word;

			line += ' ';
		}
		else
		{
			if (line.length() + word.length() > MAX_LINE)
			{
				sentence += line;
				m_chat.push_back(sentence);
				sentence.clear();
				line.clear();
				line += word;
				counter++;
			}
			else
				line += word;

			line += ' ';
		}
	}
	if (!line.empty())
		sentence += line;
	if (!sentence.empty())
		m_chat.push_back(sentence);

	m_it = m_chat.cbegin();
	m_text.setString(*m_it);
}

void Chat::keyReleasedHandler(const Event & event)
{
	switch (event.key.code)
	{
	case Keyboard::X:		// x button pressed
	case Keyboard::Z:		// or z button pressed
		++m_it;
		if (m_it != m_chat.cend())
			m_text.setString(*m_it);
		else
			m_closeScreen = true;
		break;
	}
}
