#pragma once
#include "Screen.h"

using sf::Sprite;
using sf::Text;
using std::string;
using std::vector;

class Chat : public Screen
{
public:
	Chat(const RenderWindow & window, const string & chat);
	~Chat();

	// Inherited via Screen
	virtual void draw(RenderWindow & window);
	virtual void keyReleasedHandler(const Event & event) override;

	void setChat(const string & text);

private:
	Sprite m_chatWindow;
	Text m_text;
	vector<string> m_chat;
	vector<string>::const_iterator m_it;
};

