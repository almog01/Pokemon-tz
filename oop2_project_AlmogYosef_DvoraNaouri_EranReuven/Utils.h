#pragma once
#include <SFML/Graphics.hpp>

using sf::Sprite;

enum SPOT //Spot enums for define the positions as follow for the screens, menus and more
{
	TOP_LEFT, TOP_MIDDLE, TOP_RIGHT, LEFT_MIDDLE, MIDDLE, RIGHT_MIDDLE, BOTTOM_LEFT, BOTTOM_MIDDLE, BOTTOM_RIGHT
};

class Utils //class use for translate the spot enum into origin.
{		   
public:
	static void setOrigin(Sprite & sprite, SPOT spot);
};

