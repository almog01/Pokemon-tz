#pragma once
#include "GameObject.h"

using sf::Sprite;
using sf::Event;

class Screen : public GameObject
{
public:
	Screen() = default;				// c-tor
	virtual ~Screen() = default;	// d-tor

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) = 0;

	// handles events of key released (each type of screen has different behavior for keys)
	virtual void keyReleasedHandler(const Event & event) = 0;

	// returns if the screen is still active
	bool isActive() const { return m_active; }
	
	// deactivates the screen
	void deactivate() { m_active = false; }

protected:
	Sprite m_screen;		// sprite of the screen
	bool m_active = true;	// screen activated flag
};

