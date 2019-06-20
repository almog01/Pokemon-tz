#include "StartMenu.h"
#include "ExitCommand.h"
#include "startCommand.h"
#include "LoadCommand.h"
#include "InstructionsCommand.h"

using std::make_unique;

StartMenu::StartMenu(Player& player)
	: m_player(player), m_menu(Resource::texture("main_menu"), Vector2f(1.f, 4.f), false, Resource::texture("mainMenu_arrow"))
{
	m_view.setSize({ 2944, 1949 });
	m_screen.setTexture(Resource::texture("start_menu_bg"), true);
	m_screen.setPosition({ -970, -470 });
	sf::Vector2f menuFactor = { -600, 380 };
	m_menu.setOrigin(BOTTOM_RIGHT);
	m_menu.setTextMarginY(165);
	m_menu.addCommand("", make_unique<startCommand>((*this)));
	m_menu.addCommand("", make_unique<LoadCommand>((*this), m_player));
	m_menu.addCommand("", make_unique<InstructionsCommand>());
	m_menu.addCommand("", make_unique<ExitCommand>(&*this));
	m_menu.setPosition(Vector2f(m_view.getCenter() + menuFactor));
}


StartMenu::~StartMenu()
{
}

void StartMenu::draw(RenderWindow & window)
{
	window.setView(m_view);
	window.draw(m_screen);
	m_menu.draw(window);
}

void StartMenu::keyReleasedHandler(const Event & event)
{
	m_menu.keyReleasedHandler(event);
}

void StartMenu::setTexture(sf::Texture x)
{
	m_screen.setTexture(x);
}
