#pragma once
#include "Screen.h"

using sf::Text;

enum SELECTION
{
	POKEDEX, POKEMON, BAG, PROFILE, SAVE, OPTION, EXIT
};

class Menu : public Screen
{
public:
	Menu();
	~Menu();

	// Inherited via Screen
	virtual void draw(RenderWindow & window);
	virtual void keyReleasedHandler(const Event & event) override;

private:
	Text m_text;
	Sprite m_arrow;
	SELECTION m_selection;
};

