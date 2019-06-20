#pragma once
#include "Screen.h"
#include "Menu.h"
#include "Player.h"

class StartMenu :	public Screen
{
public:
	StartMenu(Player& player);
	~StartMenu();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;

	void setTexture(sf::Texture x);


private:
	sf::View m_view;
	sf::Sprite m_backGround;
	//sf::Sprite m_menuBg;
	Menu m_menu;
	Player& m_player;


};

