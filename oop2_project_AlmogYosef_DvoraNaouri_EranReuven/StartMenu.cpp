#include "StartMenu.h"
#include "ExitCommand.h"
#include "startCommand.h"
#include "LoadCommand.h"
#include "InstructionsCommand.h"

using std::make_unique;

StartMenu::StartMenu(Player& player, shared_ptr<Music> music)
	: m_music(music), m_player(player), m_menu(Resource::texture("main_menu"), Vector2f(1.f, 4.f), false, Resource::texture("mainMenu_arrow")), m_subScreen(nullptr)
{
	m_view.setSize({ 2944, 1949 });
	m_screen.setTexture(Resource::texture("start_menu_bg"), true);
	m_screen.setPosition({ -970, -470 });
	sf::Vector2f menuFactor = { -600, 380 };
	m_menu.setOrigin(BOTTOM_RIGHT);
	m_menu.setTextMarginY(165);
	m_menu.addCommand("", make_unique<StartCommand>(*this));
	m_menu.addCommand("", make_unique<LoadCommand>(*this, m_player));
	m_menu.addCommand("", make_unique<InstructionsCommand>(m_subScreen));
	m_menu.addCommand("", make_unique<ExitCommand>(&*this, true));
	m_menu.setPosition(Vector2f(m_view.getCenter() + menuFactor));
	m_music = Resource::music("startmenu");
	m_music->play();
}


StartMenu::~StartMenu()
{
	m_music->stop();
	m_music = Resource::music("background");
	m_music->play();
}

void StartMenu::draw(RenderWindow & window)
{
	if (m_subScreen)
	{
		if (!m_subScreen->isActive())
			m_subScreen.reset();
		else
			m_subScreen->draw(window);
	}
	else 
	{
		window.setView(m_view);
		window.draw(m_screen);
		m_menu.draw(window);
	}
}

void StartMenu::keyReleasedHandler(const Event & event)
{
	if (m_subScreen)
		m_subScreen->keyReleasedHandler(event);
	else
	{
		if (event.key.code == sf::Keyboard::Enter)
			m_menu.select();
		else
			m_menu.keyReleasedHandler(event);
	}
}
