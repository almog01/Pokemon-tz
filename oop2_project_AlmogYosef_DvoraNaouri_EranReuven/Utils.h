#pragma once
#include <SFML/Graphics.hpp>

using sf::Sprite;

enum SPOT
{
	TOP_LEFT, TOP_MIDDLE, TOP_RIGHT, LEFT_MIDDLE, MIDDLE, RIGHT_MIDDLE, BOTTOM_LEFT, BOTTOM_MIDDLE, BOTTOM_RIGHT
};

class Utils
{
public:
	static void setOrigin(Sprite & sprite, SPOT spot);
};

