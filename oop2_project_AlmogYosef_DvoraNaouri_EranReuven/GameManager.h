#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "City.h"
#include "Player.h"

using sf::RenderWindow;
using sf::View;
using sf::Event;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void play();

private:
	// Creates the main window
	void createWindow();

	// Initializes all the characters
	void iniCharacters();

	// Draws the whole game objects on the window, and than displays it
	void draw();

	// Handles the events
	void handleEvents();

	// Handles the events of any keyboard button was released
	void keyReleasedHandler(const Event & event);

	// Updates all objects
	void update();

	// Members:
	Resource m_rm;			// resource manager to load the needed files
	RenderWindow m_window;	// main window
	View m_view;			// current view
	City m_city;			// current map
	Player m_player;		// the player
};

