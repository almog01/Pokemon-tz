#pragma once
#include "GameObject.h"
class Screen : public GameObject
{
public:
	Screen();
	virtual ~Screen();

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;
};

