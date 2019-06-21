#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
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
using sf::RenderWindow;
using sf::View;
using sf::Event;
using sf::Music;

class GameManager
{
public:
	GameManager();
	~GameManager();

	// Starts the game
	void play();

	void wildPokemonBattle();

private:
	// Creates the main window
	void createWindow();

	void startMenuScene();

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

	void openChat();
	void openMenu();

	void battleScene(Trainer & trainer, int battleArena = 1);
	void battleScene(Pokemon & pokemon, int battleArena = 1);

	// Members:
	Resource & m_resource;		// resource instance to load the files
	Factory & m_factory;		// factory instance to create the game objects
	RenderWindow m_window;		// main window
	View m_view;				// current view
	Map* m_map;					// current map
	Player & m_player;			// the player
	unique_ptr<Screen> m_screen;
	bool m_menuActive;			// menu active flag
	bool m_start = true;
	Music m_music;
};

