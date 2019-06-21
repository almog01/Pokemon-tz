#pragma once
#include "Screen.h"
#include "Menu.h"
#include "Player.h"

using std::unique_ptr;
using std::shared_ptr;

class StartMenu : public Screen // inherit from Screen
{
public:
	StartMenu(Player& player, shared_ptr<Music> m_music); //constructor
	~StartMenu(); //destructor

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override; //draw function, override Screen virtual func
	virtual void keyReleasedHandler(const Event & event) override; //KeyReleasedHandler function, override Screen virtual func

private:
	sf::View m_view; //member to change the screen view
	Menu m_menu; //member to define the main menu
	Player& m_player; //reference to the player, for load function
	unique_ptr<Screen> m_subScreen; //sub screen member, for the instructions screen
	shared_ptr<Music> m_music; //music member, to play the bg music in the open screen
};

