#include "GameManager.h"
#include "Settings.h"
#include "City.h"
#include "Chat.h"
#include "Menu.h"

using std::make_unique;
using sf::VideoMode;
using sf::Color;
using sf::Keyboard;
using sf::Clock;
using sf::Time;

GameManager::GameManager() : m_resource(Resource::instance()), m_factory(Factory::instance()), m_screen(nullptr)
{
}


GameManager::~GameManager()
{
}

void GameManager::play()
{
	createWindow();
	initCharacters();

	Clock clock;
	Time accumulator = Time::Zero;
	Time fps = sf::seconds(1.f / Settings::FPS());

	while (m_window.isOpen())	// main window loop
	{
		handleEvents();		// handle each events

		m_window.clear();	// clear the main window

		while (accumulator > fps) {
			accumulator -= fps;
			update();
		}
		draw();				// clear, draw and display each object on the main window
		m_window.display();	// display the main window after all has been drawn
		accumulator += clock.restart();
	}
}

void GameManager::createWindow()
{
	m_window.create(VideoMode(1024, 600), Settings::WINDOW_TITLE(), sf::Style::Close | sf::Style::Resize);	// create fullscreen window
	//m_window.create(VideoMode(), Settings::WINDOW_TITLE(), sf::Style::Fullscreen);	// create fullscreen window
	m_view.setSize(float(VideoMode::getDesktopMode().width / 2.8f), float(VideoMode::getDesktopMode().height / 2.8f));
	m_map = Factory::map("pallet");
}

void GameManager::initCharacters()
{
	m_player.setPosition(Vector2f(180.f, 550.f));
	m_player.setMap(m_map);
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
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
			m_screen = make_unique<Menu>();
			break;
		case Keyboard::X:		// x pressed
			NPC* npc = nullptr;
			if (m_map->tryChat(m_player.getPov(), npc))
				openChat(npc);
			break;
		}
	}
}

void GameManager::update()
{
	if (m_screen)
	{
		if (m_screen->isFinished())
			m_screen.reset();
	}
	else
	{
		m_player.update();
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

void GameManager::openChat(NPC * npc)
{
	m_screen = make_unique<Chat>(m_window, npc->getChat());
}
