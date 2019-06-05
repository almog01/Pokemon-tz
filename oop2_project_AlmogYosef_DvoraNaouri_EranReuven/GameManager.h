#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "Factory.h"
#include "Map.h"
#include "Player.h"
#include <unordered_map>
#include <memory>

using std::string;
using sf::RenderWindow;
using sf::View;
using sf::Event;

class GameManager
{
public:
	GameManager();
	~GameManager();

	// Starts the game
	void play();

private:
	// Creates the main window
	void createWindow();

	// Initializers
	void initCharacters();

	// Draws the whole game objects on the window, and than displays it
	void draw();

	// Event Handlers
	void handleEvents();
	void keyReleasedHandler(const Event & event);

	// Updates all objects
	void update();

	void updateMap(const string & name);

	// Members:
	Resource & m_resource;	// resource occurrence to load the needed files
	Factory & m_factory;	// factory occurrence to create the needed objects
	RenderWindow m_window;	// main window
	View m_view;			// current view
	Map * m_map;			// current map
	Player m_player;		// the player
};

