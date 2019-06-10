#include "Screen.h"



Screen::Screen()
{
}


Screen::~Screen()
{
}

void Screen::draw(RenderWindow & window)
{
	window.draw(m_sprite);
}
