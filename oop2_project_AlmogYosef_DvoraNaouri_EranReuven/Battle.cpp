#include "Battle.h"
#include "Factory.h"
#include "FightCommand.h"
#include "BagCommand.h"
#include "PokemonListCommand.h"
#include "ExitCommand.h"
#include <cctype>

using sf::Color;
using std::to_string;
using std::make_unique;

const unsigned TEXT_SIZE = 14U;

Battle::Battle(Trainer & player, Trainer & enemy, int battleType)
	: m_menu(Resource::texture("battle_menu_frame"), Vector2f(2.f, 2.f), false), m_player(player), m_enemy(enemy),
	m_playerName("", Resource::font, TEXT_SIZE), m_playerLevel("", Resource::font, TEXT_SIZE), m_playerHP("", Resource::font, TEXT_SIZE),
	m_enemyName("", Resource::font, TEXT_SIZE), m_enemyLevel("", Resource::font, TEXT_SIZE)
{
	m_screen.setTexture(Resource::texture("battle"));
	battleArenaLoader(battleType);
	// initialize menu background
	m_menuBg.setTexture(Resource::texture("battle_menu_bg"), true);
	m_menuBg.setOrigin(m_menuBg.getGlobalBounds().width, m_menuBg.getGlobalBounds().height);
	m_menuBg.setPosition(Vector2f(m_view.getCenter().x + (m_view.getSize().x / 2.f), m_view.getCenter().y + (m_view.getSize().y / 2.f)));
	// 2 choosed pokemons
	choosePokemon(true, 0);
	choosePokemon(false, 0);
	// initialize menu
	m_menu.setOrigin(BOTTOM_RIGHT);
	m_menu.setPosition(Vector2f(m_view.getCenter().x + m_view.getSize().x / 2.f, m_view.getCenter().y + m_view.getSize().y / 2.f));
	m_menu.addCommand("Fight", std::make_unique<FightCommand>(m_view, m_subScreen, *m_playerPokemon, m_playerUsedAbility));
	m_menu.addCommand("Bag", std::make_unique<BagCommand>());
	m_menu.addCommand("Pokemon", std::make_unique<PokemonListCommand>(m_subScreen, m_player, true));
	m_menu.addCommand("Run", std::make_unique<ExitCommand>(m_menu));
	// initialize statbars
	m_playerStatbar.setTexture(Resource::texture("battle_player_statbar"), true);
	m_playerStatbar.setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(0.f, -5.f));
	m_enemyStatbar.setTexture(Resource::texture("battle_enemy_statbar"), true);
	m_enemyStatbar.setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(-110.f, -70.f));
	// initialize hpbars
	m_playerHpBar.setTexture(Resource::texture("battle_hpbar"), true);
	m_playerHpBar.setPosition(m_playerStatbar.getPosition() + Vector2f(48.f, 17.f));
	m_enemyHpBar.setTexture(Resource::texture("battle_hpbar"), true);
	m_enemyHpBar.setPosition(m_enemyStatbar.getPosition() + Vector2f(39.f, 17.f));
	// initialize expbar
	m_expBar.setTexture(Resource::texture("battle_expbar"));
	m_expBar.setPosition(m_playerStatbar.getPosition() + Vector2f(32.f, 33.f));
	// initialize texts
	m_playerName.setFillColor(Color::Black);
	m_playerName.setString((*m_playerPokemon)->getName());
	m_playerName.setPosition(m_playerStatbar.getPosition() + Vector2f(15.f, -1.f));
	m_playerLevel.setFillColor(Color::Black);
	m_playerLevel.setString("Lv" + to_string((*m_playerPokemon)->getLevel()));
	m_playerLevel.setPosition(m_playerStatbar.getPosition() + Vector2f(75.f, -1.f));
	m_playerHP.setFillColor(Color::Black);
	m_playerHP.setString(to_string((*m_playerPokemon)->getHp()) + "/" + to_string((*m_playerPokemon)->getMaxHp()));
	m_playerHP.setPosition(m_playerStatbar.getPosition() + Vector2f(62.f, 17.f));
	m_enemyName.setFillColor(Color::Black);
	m_enemyName.setString((*m_enemyPokemon)->getName());
	m_enemyName.setPosition(m_enemyStatbar.getPosition() + Vector2f(6.f, -1.f));
	m_enemyLevel.setFillColor(Color::Black);
	m_enemyLevel.setString("Lv" + to_string((*m_enemyPokemon)->getLevel()));
	m_enemyLevel.setPosition(m_enemyStatbar.getPosition() + Vector2f(66.f, -1.f));
}


Battle::~Battle()
{
}

void Battle::draw(RenderWindow & window)
{
	window.draw(m_screen);
	window.draw(m_menuBg);
	window.draw(m_playerStatbar);
	window.draw(m_playerHpBar);
	window.draw(m_expBar);
	window.draw(m_playerName);
	window.draw(m_playerLevel);
	window.draw(m_playerHP);
	window.draw(m_enemyStatbar);
	window.draw(m_enemyHpBar);
	window.draw(m_enemyName);
	window.draw(m_enemyLevel);
	(*m_playerPokemon)->draw(window);
	(*m_enemyPokemon)->draw(window);
	m_menu.draw(window);
	m_active = m_menu.isActive();
	if (m_subScreen)
	{
		if (!m_subScreen->isActive())
			m_subScreen.reset();
		else
			m_subScreen->draw(window);
	}
	else
		window.setView(m_view);
	if (m_msg)
	{
		if (!m_msg->isActive())
		{
			m_msg.reset();
			if (!m_isPlayerTurn)
				execEnemyTurn();
		}
		else
			m_msg->draw(window);
	}	
}

void Battle::keyReleasedHandler(const Event & event)
{
	if (m_msg)
		m_msg->keyReleasedHandler(event);
	else if (m_subScreen)
	{
		m_subScreen->keyReleasedHandler(event);
		if (m_isPlayerTurn)
			execPlayerTurn();
	}
	else
		m_menu.keyReleasedHandler(event);
}

void Battle::battleArenaLoader(int battleType)
{
	switch (battleType)
	{
	case 1:
		m_view = sf::View(sf::FloatRect(2.f, 22.f, 240.f, 160.f));
		break;
	}
}

void Battle::choosePokemon(bool isPlayer, int index)
{
	if (isPlayer)
	{
		m_playerPokemon = m_player.begin() + index;
		(*m_playerPokemon)->setTexture("back");
		(*m_playerPokemon)->setOrigin(BOTTOM_MIDDLE);
		(*m_playerPokemon)->setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(-55.f, 32.f));
	}
	else
	{
		m_enemyPokemon = m_enemy.begin() + index;
		(*m_enemyPokemon)->setTexture("front");
		(*m_enemyPokemon)->setOrigin(BOTTOM_MIDDLE);
		(*m_enemyPokemon)->setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(60.f, -15.f));
	}
}

void Battle::execPlayerTurn()
{
	if (m_playerUsedAbility)	// if an ability was used
	{
		m_msg = make_unique<Chat>(Resource::texture("battle_menu_bg"), m_view, (*m_playerPokemon)->getName() + " used " + m_playerUsedAbility->getName(), Color::White);
		m_playerUsedAbility->use((*m_enemyPokemon));
		m_playerUsedAbility = nullptr;
		auto temp = (*m_enemyPokemon)->getHpBar();
		m_enemyHpBar.setTextureRect(temp.getTextureRect());
		m_isPlayerTurn = false;
	}
}

void Battle::execEnemyTurn()
{
	Ability* enemyUsedAbility = (*m_enemyPokemon)->getRandAbility();
	m_msg = make_unique<Chat>(Resource::texture("battle_menu_bg"), m_view, "Enemy " + (*m_enemyPokemon)->getName() + " used " + enemyUsedAbility->getName(), Color::White);
	enemyUsedAbility->use((*m_playerPokemon));
	auto temp = (*m_playerPokemon)->getHpBar();
	m_playerHpBar.setTextureRect(temp.getTextureRect());
	m_isPlayerTurn = true;
}

