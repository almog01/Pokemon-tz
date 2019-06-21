#include "GameManager.h"
#include "StartMenu.h"
#include "Chat.h"
#include "Battle.h"
#include "PokemonListCommand.h"
#include "SaveCommand.h"
#include "ExitCommand.h"

using std::make_unique;
using sf::VideoMode;
using sf::Color;
using sf::Keyboard;
using sf::Clock;
using sf::Time;

const int WILD_RANDOMNESS = 120;
const int UPS = 60;			// updates per second

GameManager::GameManager() 
	: m_resource(Resource::instance()), m_factory(Factory::instance()), m_player(Player::instance()), m_screen(nullptr), m_menuActive(false)
{
	createWindow();
	initPlayer();
	startMenuScene();
	m_music = Resource::music("background");
}


GameManager::~GameManager()
{
}

void GameManager::play()
{
	Clock clock;
	Time accumulator = Time::Zero;
	Time ups = sf::seconds(1.f / UPS);

	while (m_window.isOpen())	// main window loop
	{
		handleEvents();		// handle each events

		m_window.clear();	// clear the main window

		while (accumulator > ups) {
			accumulator -= ups;
			update();
		}
		draw();				// clear, draw and display each object on the main window
		m_window.display();	// display the main window after all has been drawn
		accumulator += clock.restart();
	}
}

void GameManager::wildPokemonBattle()
{
	int random = rand() % WILD_RANDOMNESS;
	if (random == 0)
	{
		Pokemon wild = m_map->getWildPokemon();
		battleScene(wild);
	}
}

void GameManager::createWindow()
{
	m_window.create(VideoMode(1024, 600), "Pokemon-tz", sf::Style::Close | sf::Style::Resize);	// create fullscreen window
	//m_window.create(VideoMode(), "Pokemon-tz", sf::Style::Fullscreen);	// create fullscreen window
	m_view.setSize(float(VideoMode::getDesktopMode().width / 2.8f), float(VideoMode::getDesktopMode().height / 2.8f));
	m_map = Factory::map("home");
}

void GameManager::startMenuScene()
{
	m_screen = make_unique<StartMenu>(m_player, m_music);
}

void GameManager::initPlayer()
{
	m_player.setPosition(Vector2f(134.f, 42.f));
	m_player.setMap(m_map);
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
	m_player.addPokemon(Factory::pokemon("pikachu", 5));
	m_player.addPokemon(Factory::pokemon("mewtwo", 5));
	m_player.addPokemon(Factory::pokemon("mew", 5));
	m_player.addPokemon(Factory::pokemon("charizard", 5));
	m_player.addPokemon(Factory::pokemon("blastoise", 5));
	m_player.addPokemon(Factory::pokemon("venusaur", 5));
}

void GameManager::draw()
{
	m_map->draw(m_window);
	m_player.draw(m_window);
	if (m_screen)
		m_screen->draw(m_window);
}

void GameManager::handleEvents()
{
	Event event;
	while (m_window.pollEvent(event))	// main event loop
	{
		switch (event.type)
		{
		case Event::Closed:		// event of windows closed
			m_window.close();
			break;
		case Event::KeyReleased:	// event of key released
			keyReleasedHandler(event);
			break;
		}
	}
}

void GameManager::keyReleasedHandler(const Event & event)
{
	if (m_screen)
	{
		if (event.key.code == Keyboard::Escape)
		{
			m_window.close();	// close the game
			return;
		}
		else if (m_menuActive && event.key.code == Keyboard::Enter)
		{
			m_menuActive = false;
			m_screen.reset();
		}
		else
			m_screen->keyReleasedHandler(event);
	}
	else
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:	// escape pressed
			m_window.close();	// close the game
			break;
		case Keyboard::Enter:	// enter pressed
			openMenu();
			break;
		case Keyboard::Z:		// z pressed
			openChat();
			break;
		}
	}
}

void GameManager::update()
{
	if (m_screen)
	{
		if (!m_screen->isActive())
			m_screen.reset();
	}
	else
	{
		m_player.update(*this);
		m_map->checkCollision(m_player);
		if (m_map->getName() != m_player.getMap())
			updateMap(m_player.getMap());
		// Update view
		m_view.setCenter(m_player.getPosition());
		m_window.setView(m_view);
	}
}

void GameManager::updateMap(const string & name)
{
	m_map = Factory::map(name);
	m_player.setMap(m_map);
}

void GameManager::openChat()
{
	NPC* npc = nullptr;
	if (m_map->tryChat(m_player.getPov(), npc))
	{
		TrainerNPC* trainer = dynamic_cast<TrainerNPC*>(npc);
		if (trainer)
			battleScene(*trainer);
		else
			npc->startChat(m_screen, m_window.getView());
	}
}

void GameManager::openMenu()
{
	auto menu = make_unique<Menu>(Resource::texture("menu"), Vector2f(1, 3));
	int temp;
	menu->addCommand("POKEMON", make_unique<PokemonListCommand>(m_screen, m_player, temp));
	menu->addCommand("SAVE", make_unique<SaveCommand>(m_player, m_screen, m_window));
	menu->addCommand("EXIT", make_unique<ExitCommand>(menu.get()));
	menu->setOrigin(RIGHT_MIDDLE);
	menu->setPosition(Vector2f(m_view.getCenter().x + (m_view.getSize().x / 2.f), m_view.getCenter().y));
	m_menuActive = true;
	m_screen = std::move(menu);
}

void GameManager::battleScene(Trainer & trainer)
{
	if (!m_player.isDefeated() && !trainer.isDefeated())
	{
		m_music->stop();
		m_screen = make_unique<Battle>(m_player, trainer, m_music);
	}
}

void GameManager::battleScene(Pokemon & pokemon)
{
	if (!m_player.isDefeated())
	{
		m_music->stop();
		m_screen = make_unique<Battle>(m_player, pokemon, m_music);
	}
}
