#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
using sf::RectangleShape;
using sf::Texture;
using sf::Vector2f;
using sf::RenderWindow;
using sf::Text;


class Chat : public Menu
{
public:
	Chat(const Vector2f &pos,		
		const Vector2f & size,
		string text);	

	void draw(RenderWindow & window);
	Vector2f getPosition() const;
	bool contains(const Vector2f & pos) const;

	~Chat();
private:
	RectangleShape m_chatWindow;
	Text m_text;

};

