#include "Chat.h"
#include <sstream>

using sf::Vector2f;
using sf::Keyboard;
using std::istringstream;

const unsigned TEXT_SIZE = 15U;
const float TEXT_MARGIN_X = 11.f;
const float TEXT_MARGIN_Y = 4.f;
const size_t MAX_LINE = 39;

Chat::Chat(const Texture & frameTexture, const View & view, const string & chat, Color textColor)
{
	// initialize chat window
	m_screen.setTexture(frameTexture, true);
	m_screen.setOrigin(m_screen.getGlobalBounds().width / 2, m_screen.getGlobalBounds().height);
	m_screen.setPosition(Vector2f(view.getCenter().x, view.getCenter().y + (view.getSize().y / 2.f)));

	// initialize text
	m_text.setFont(Resource::font);
	m_text.setCharacterSize(TEXT_SIZE);
	m_text.setFillColor(textColor);
	auto frameBounds = m_screen.getGlobalBounds();
	m_text.setPosition(Vector2f(frameBounds.left + TEXT_MARGIN_X, frameBounds.top + TEXT_MARGIN_Y));
	
	// set chat
	setChat(chat);
}


Chat::~Chat()
{
}

void Chat::draw(RenderWindow & window)
{
	window.draw(m_screen);
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
			m_active = false;
		break;
	}
}
