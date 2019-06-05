#include "GameManager.h"
#include "Settings.h"
#include "City.h"

using sf::VideoMode;
using sf::Color;
using sf::Keyboard;
using sf::Clock;
using sf::Time;

GameManager::GameManager() : m_resource(Resource::instance()), m_factory(Factory::instance())
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
	m_window.create(VideoMode(1366, 768), Settings::WINDOW_TITLE(), sf::Style::Close | sf::Style::Resize);	// create fullscreen window
	//m_window.create(VideoMode(), Settings::WINDOW_TITLE(), sf::Style::Fullscree	Vector2f centerWindow(float(VideoMode::getDesktopMode().width / 2), float(VideoMode::getDesktopMode().height / 2));
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
	switch (event.key.code)
	{
	case Keyboard::Escape:	// escape button pressed
		m_window.close();	// close the game
		break;
	}
}

void GameManager::update()
{
	m_player.update();
	m_map->checkCollision(m_player);
	if (m_map->getName() != m_player.getMap())
		updateMap(m_player.getMap());
	// Update view
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
}

void GameManager::updateMap(const string & name)
{
	m_map = Factory::map(name);
	m_player.setMap(m_map);
	m_player.setPosition(Vector2f(50.f, 50.f));
}
