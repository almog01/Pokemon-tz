#include "StartMenu.h"
#include "ExitCommand.h"
#include "startCommand.h"
#include "LoadCommand.h"
#include "InstructionsCommand.h"

using std::make_unique;

/*Constructor will start the members in the init line, it gets a reference to the player and a pointer to the music.
the player is for load functions and the music is for the background music.*/
StartMenu::StartMenu(Player& player, shared_ptr<Music> music)
	: m_music(music), m_player(player), m_menu(Resource::texture("main_menu"), Vector2f(1.f, 4.f), false, Resource::texture("mainMenu_arrow")), m_subScreen(nullptr)
{
	//setting view, background and screen functions for the start menu.
	m_view.setSize({ 2944, 1949 });
	m_screen.setTexture(Resource::texture("start_menu_bg"), true);
	m_screen.setPosition({ -970, -470 });
	sf::Vector2f menuFactor = { -600, 380 };

	//setting the menu functions, with the right commands.
	m_menu.setOrigin(BOTTOM_RIGHT);
	m_menu.setTextMarginY(165);
	m_menu.addCommand("", make_unique<StartCommand>(*this));
	m_menu.addCommand("", make_unique<LoadCommand>(*this, m_player));
	m_menu.addCommand("", make_unique<InstructionsCommand>(m_subScreen));
	m_menu.addCommand("", make_unique<ExitCommand>(&*this, true));
	m_menu.setPosition(Vector2f(m_view.getCenter() + menuFactor));

	//setting the background music.
	m_music = Resource::music("startmenu");
	m_music->play();
}

//Destructor. will stop the music when we call it and start the
//in game music
StartMenu::~StartMenu()
{
	m_music->stop();
	m_music = Resource::music("background");
	m_music->play();
}

void StartMenu::draw(RenderWindow & window)
{
	/*in case sub screen is open, will do the first if*/
	if (m_subScreen)
	{
		if (!m_subScreen->isActive())
			m_subScreen.reset();
		else
			m_subScreen->draw(window);
	}
	else //in any other default case
	{
		window.setView(m_view);
		window.draw(m_screen);
		m_menu.draw(window);
	}
}

void StartMenu::keyReleasedHandler(const Event & event)
{
	if (m_subScreen) //in case we have subscreen open
		m_subScreen->keyReleasedHandler(event);
	else //in any other default case
	{
		if (event.key.code == sf::Keyboard::Enter)
			m_menu.select();
		else
			m_menu.keyReleasedHandler(event);
	}
}
