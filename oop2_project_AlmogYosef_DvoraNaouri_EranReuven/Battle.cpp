#include "Battle.h"
#include "Factory.h"
#include "FightCommand.h"
#include "BagCommand.h"
#include "PokemonCommand.h"
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
	m_p1 = m_player.getPokemon(0);
	m_p1->setTexture("back");
	m_p1->setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(-85.f, -17.f));
	m_p2 = m_enemy.getPokemon(0);
	m_p2->setTexture("front");
	m_p2->setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(40.f, -60.f));
	// initialize menu
	m_menu.setOrigin(BOTTOM_RIGHT);
	m_menu.setPosition(Vector2f(m_view.getCenter().x + m_view.getSize().x / 2.f, m_view.getCenter().y + m_view.getSize().y / 2.f));
	m_menu.addCommand("Fight", std::make_unique<FightCommand>(m_view, m_subScreen, m_p1, m_playerUsedAbility));
	m_menu.addCommand("Bag", std::make_unique<BagCommand>());
	m_menu.addCommand("Pokemon", std::make_unique<PokemonCommand>());
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
	m_playerName.setString(m_p1->getName());
	m_playerName.setPosition(m_playerStatbar.getPosition() + Vector2f(15.f, -1.f));
	m_playerLevel.setFillColor(Color::Black);
	m_playerLevel.setString("Lv" + to_string(m_p1->getLevel()));
	m_playerLevel.setPosition(m_playerStatbar.getPosition() + Vector2f(75.f, -1.f));
	m_playerHP.setFillColor(Color::Black);
	m_playerHP.setString(to_string(m_p1->getHp()) + "/" + to_string(m_p1->getMaxHp()));
	m_playerHP.setPosition(m_playerStatbar.getPosition() + Vector2f(62.f, 17.f));
	m_enemyName.setFillColor(Color::Black);
	m_enemyName.setString(m_p2->getName());
	m_enemyName.setPosition(m_enemyStatbar.getPosition() + Vector2f(6.f, -1.f));
	m_enemyLevel.setFillColor(Color::Black);
	m_enemyLevel.setString("Lv" + to_string(m_p2->getLevel()));
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
	m_p1->draw(window);
	m_p2->draw(window);
	m_menu.draw(window);
	m_active = m_menu.isActive();
	if (m_subScreen)
	{
		if (!m_subScreen->isActive())
			m_subScreen.reset();
		else
			m_subScreen->draw(window);
	}
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
	window.setView(m_view);
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

void Battle::updateHpBar(Sprite & bar, float max, float hp)
{
	auto rect = bar.getTextureRect();
	static int rectWidth = rect.width;
	if (hp <= 0)
		bar.setTextureRect(sf::IntRect(rect.left, rect.top, 0, rect.height));
	else
		bar.setTextureRect(sf::IntRect(rect.left, rect.top, int((hp / max) * rectWidth), rect.height));
}

void Battle::execPlayerTurn()
{
	if (m_playerUsedAbility)	// if an ability was used
	{
		m_msg = make_unique<Chat>(Resource::texture("battle_menu_bg"), m_view, m_p1->getName() + " used " + m_playerUsedAbility->getName(), Color::White);
		m_playerUsedAbility->use(m_p2);
		m_playerUsedAbility = nullptr;
		updateHpBar(m_enemyHpBar, float(m_p2->getMaxHp()), float(m_p2->getHp()));
		m_isPlayerTurn = false;
	}
}

void Battle::execEnemyTurn()
{
	Ability* enemyUsedAbility = m_p2->getRandAbility();
	m_msg = make_unique<Chat>(Resource::texture("battle_menu_bg"), m_view, "Enemy " + m_p2->getName() + " used " + enemyUsedAbility->getName(), Color::White);
	enemyUsedAbility->use(m_p1);
	updateHpBar(m_playerHpBar, float(m_p1->getMaxHp()), float(m_p1->getHp()));
	m_isPlayerTurn = true;
}

