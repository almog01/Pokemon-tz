#include "GameManager.h"
#include "Settings.h"

using sf::VideoMode;
using sf::Color;
using sf::Keyboard;
using sf::Clock;
using sf::Time;

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::play()
{
	createWindow();
	iniCharacters();

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
	m_window.create(VideoMode(), Settings::WINDOW_TITLE(), sf::Style::Fullscreen);	// create fullscreen window
	m_view.setSize(float(VideoMode::getDesktopMode().width) / 1.5f, float(VideoMode::getDesktopMode().height) / 1.5f);
	m_city.loadMap("vermillion");
}

void GameManager::iniCharacters()
{
	Vector2f centerWindow(float(VideoMode::getDesktopMode().width / 2), float(VideoMode::getDesktopMode().height / 2));
	m_player.setPosition(centerWindow + sf::Vector2f{-30.0f, +50.0f});
	m_player.setMapData(m_city.getMapData());
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
}

void GameManager::draw()
{
	m_city.draw(m_window);
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

	// Update view
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
}
