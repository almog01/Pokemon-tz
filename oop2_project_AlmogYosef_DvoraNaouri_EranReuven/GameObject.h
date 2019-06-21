#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"

using sf::RenderWindow;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	// draws the object on the window
	virtual void draw(RenderWindow & window) = 0;
};

