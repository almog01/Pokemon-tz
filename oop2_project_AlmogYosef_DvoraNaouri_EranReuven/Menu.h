#pragma once
#include "GameObject.h"
class Menu : public GameObject
{
public:
	Menu();
	virtual ~Menu();

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;

	// Inherited via GameObject
	virtual void setTextureRect(const IntRect & rect) override;
};

