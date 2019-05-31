#pragma once
#include "GameObject.h"
class Screen : public GameObject
{
public:
	Screen();
	virtual ~Screen();

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;

	// Inherited via GameObject
	virtual void setTextureRect(const IntRect & rect) override;
};

