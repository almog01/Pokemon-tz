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

	bool isActive() const { return m_active; }
	void deactivate() { m_active = false; }

protected:
	Sprite m_screen;
	bool m_active = true;	// screen activated flag
};

