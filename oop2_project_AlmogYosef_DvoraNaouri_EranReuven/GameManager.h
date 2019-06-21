#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "Factory.h"
#include "Map.h"
#include "Player.h"
#include "Screen.h"
#include "NPC.h"
#include "TrainerNPC.h"
#include "Menu.h"
#include <unordered_map>
#include <memory>

using std::string;
using std::unique_ptr;
using std::shared_ptr;
using sf::RenderWindow;
using sf::View;
using sf::Event;

class GameManager
{
public:
	GameManager();	// c-tor
	~GameManager();	// d-tor

	// Starts the game
	void play();

	// Start battle with wild pokemon (pokemon in grass)
	void wildPokemonBattle();

private:
	// Creates the main window
	void createWindow();

	// Creates the start menu
	void startMenuScene();

	// Initializes player
	void initPlayer();

	// Draws the whole game objects on the window, and than displays it
	void draw();

	// Event Handlers
	void handleEvents();
	void keyReleasedHandler(const Event & event);

	// Updates all objects
	void update();

	// Updates current map
	void updateMap(const string & name);

	// Opens a chat with npc if close enougth
	void openChat();

	// Opens the main menu
	void openMenu();

	// Starts a battle with trainer / wild pokemon
	void battleScene(Trainer & trainer);
	void battleScene(Pokemon & pokemon);

	// Members:
	Resource & m_resource;			// resource instance to load the files
	Factory & m_factory;			// factory instance to create the game objects
	RenderWindow m_window;			// main window
	View m_view;					// current view
	Map* m_map;						// current map
	Player & m_player;				// the player
	unique_ptr<Screen> m_screen;	// polymorphic screen to display different kind of screen in each part of the game 
	bool m_menuActive;				// menu active flag
	shared_ptr<Music> m_music;		// for background music
};

