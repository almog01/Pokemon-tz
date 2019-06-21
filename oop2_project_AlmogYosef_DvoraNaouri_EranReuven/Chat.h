#pragma once
#include "Screen.h"

using sf::View;
using sf::Text;
using sf::Texture;
using sf::Color;
using std::string;
using std::vector;

class Chat : public Screen
{
public:
	// c-tor
	Chat(const Texture & frameTexture, const View & view, const string & chat, Color textColor = Color::Black);
	// d-tor
	~Chat();

	// Inherited via Screen
	virtual void draw(RenderWindow & window);
	virtual void keyReleasedHandler(const Event & event) override;

	// splits a string and builds the m_chat vector from it
	void setChat(const string & text);

private:
	Text m_text;			// text instance
	vector<string> m_chat;	// vector of string for a splitted chat
	vector<string>::const_iterator m_it;	// chat iterator
};

