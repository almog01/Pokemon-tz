#include "Chat.h"
#include <sstream>

using sf::Vector2f;
using sf::Keyboard;
using std::istringstream;

const unsigned TEXT_SIZE = 15U;		// text size
const float TEXT_MARGIN_X = 11.f;	// distance in x between the texts
const float TEXT_MARGIN_Y = 4.f;	// distance in y between the texts
const size_t MAX_LINE = 39;			// max line length

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
	// draw chat
	window.draw(m_screen);
	window.draw(m_text);
}

void Chat::setChat(const string & text)
{
	// create an istringstream and split the text into sentences
	istringstream iss(text);
	string word;		// single word
	string line;		// line = collection of words
	string sentence;	// sentence = 2 lines
	int counter = 0;	// counter to check if the line is first or second

	while (iss >> word)		// for each word
	{
		if (counter % 2 == 0)	// if building first line
		{
			if (line.length() + word.length() > MAX_LINE)	// if adding the word will exceed the max line length
			{
				// add the line to the sentence and start building the next line
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
		else					// if building second line
		{
			if (line.length() + word.length() > MAX_LINE)	// if adding the word will exceed the max line length
			{
				// add the line to the sentence and add the sentence to the chat vector, than start building the next line
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
	// if there are unfinished line of sentence, add them to the appropriate area
	if (!line.empty())
		sentence += line;
	if (!sentence.empty())
		m_chat.push_back(sentence);

	m_it = m_chat.cbegin();		// init iterator to the first chat
	m_text.setString(*m_it);	// set text string
}

void Chat::keyReleasedHandler(const Event & event)
{
	switch (event.key.code)
	{
	case Keyboard::X:		// x button pressed
	case Keyboard::Z:		// or z button pressed
		// precede the iterator for each string until the end
		++m_it;
		if (m_it != m_chat.cend())
			m_text.setString(*m_it);
		else
			m_active = false;
		break;
	}
}
