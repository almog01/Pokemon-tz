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
	Chat(const Texture & frameTexture, const View & view, const string & chat, Color textColor = Color::Black);
	~Chat();

	// Inherited via Screen
	virtual void draw(RenderWindow & window);
	virtual void keyReleasedHandler(const Event & event) override;

	void setChat(const string & text);

private:
	Text m_text;
	vector<string> m_chat;
	vector<string>::const_iterator m_it;
};

