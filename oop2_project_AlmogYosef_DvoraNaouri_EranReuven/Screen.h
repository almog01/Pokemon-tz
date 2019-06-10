#pragma once
#include "GameObject.h"

using sf::Event;

class Screen : public GameObject
{
public:
	Screen();
	virtual ~Screen();

	virtual void keyReleasedHandler(const Event & event) = 0;

	bool isFinished() const { return m_isFinished; }
	virtual void draw(RenderWindow & window) override;

protected:
	bool m_isFinished = false;	// screen finished flag
	sf::Sprite m_sprite;
};

