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

protected:
	bool m_isFinished = false;	// screen finished flag
};

