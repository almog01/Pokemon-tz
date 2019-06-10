#pragma once
#include "GameObject.h"

using sf::Sprite;
using sf::Event;

class Screen : public GameObject
{
public:
	Screen();
	virtual ~Screen();

	// Inherited via GameObject
	virtual void draw(RenderWindow & window);

	virtual void keyReleasedHandler(const Event & event) = 0;

	bool isFinished() const { return m_closeScreen; }

protected:
	Sprite m_sprite;
	bool m_closeScreen = false;	// screen finished flag
};

