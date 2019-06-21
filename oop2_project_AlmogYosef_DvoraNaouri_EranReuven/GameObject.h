#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"

using sf::RenderWindow;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void draw(RenderWindow & window) = 0;
};

