#include "Chat.h"
const unsigned TEXT_PADDING = 20;


Chat::Chat(const Vector2f & pos, const Vector2f & size, string text)
{
	m_chatWindow.setTexture(&Resource::texture("cw"));
	m_chatWindow.setSize(size);
	m_chatWindow.setPosition(pos);
	m_chatWindow.setOrigin(m_chatWindow.getGlobalBounds().width / 2, m_chatWindow.getGlobalBounds().height / 2);
}

Chat::ch;
m_text.setString(text);							
m_text.setFont(rm.getFont());						
m_text.setCharacterSize(btnSize - TEXT_PADDING);	// text_size = button_size - padding (to make the text "inside" the button)
m_text.setFillColor(sf::Color::Red);				// color = red
m_text.setPosition(m_button.getPosition());			// same position as the button
m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().width / 2);	// set origin to the middle


Chat::~Chat()
{
}


void Chat::draw(RenderWindow & window)
{
	window.draw(m_chatWindow);
	window.draw(m_text);
}

Vector2f Chat::getPosition() const
{
	return m_chatWindow.getPosition();
}

bool Chat::contains(const Vector2f & pos) const
{
	return m_chatWindow.getGlobalBounds().contains(pos);
}

