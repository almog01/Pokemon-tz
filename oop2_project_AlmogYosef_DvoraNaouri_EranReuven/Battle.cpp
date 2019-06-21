#include "Battle.h"
#include "Factory.h"
#include "FightCommand.h"
#include "PokemonListCommand.h"
#include "ExitCommand.h"
#include <cctype>

using sf::Color;
using std::to_string;
using std::make_unique;

const unsigned TEXT_SIZE = 14U;
const float BASE_EXP = 45;

Battle::Battle(Player & player, Trainer & enemy, int battleType)
	: m_menu(Resource::texture("battle_menu_frame"), Vector2f(2.f, 2.f), false), m_player(player), m_enemy(&enemy),
	m_playerName("", Resource::font, TEXT_SIZE), m_playerLevel("", Resource::font, TEXT_SIZE), m_playerHP("", Resource::font, TEXT_SIZE),
	m_enemyName("", Resource::font, TEXT_SIZE), m_enemyLevel("", Resource::font, TEXT_SIZE)
{
	// initialize battle screen
	initBattle(battleType);
	// choose enemy pokemon
	m_enemyCurrPokemon = getFirstAlivePokemon(enemy);
	if (m_enemyCurrPokemon != -1)
		choosePokemon(false, m_enemyCurrPokemon);
	else
		m_active = false;
	// initialize enemy texts
	m_enemyName.setFillColor(Color::Black);
	m_enemyName.setPosition(m_enemyStatbar.getPosition() + Vector2f(6.f, -1.f));
	m_enemyLevel.setFillColor(Color::Black);
	m_enemyLevel.setPosition(m_enemyStatbar.getPosition() + Vector2f(66.f, -1.f));
}

Battle::Battle(Player & player, Pokemon & wildPokemon, int battleType)
	: m_menu(Resource::texture("battle_menu_frame"), Vector2f(2.f, 2.f), false), m_player(player), m_enemyPokemon(make_shared<Pokemon>(wildPokemon)),
	m_playerName("", Resource::font, TEXT_SIZE), m_playerLevel("", Resource::font, TEXT_SIZE), m_playerHP("", Resource::font, TEXT_SIZE),
	m_enemyName("", Resource::font, TEXT_SIZE), m_enemyLevel("", Resource::font, TEXT_SIZE)
{
	// initialize battle screen
	initBattle(battleType);
	// initialize wild pokemon stats
	m_enemyPokemon = make_shared<Pokemon>(wildPokemon);
	m_enemyPokemon->setTexture("front");
	m_enemyPokemon->setOrigin(BOTTOM_MIDDLE);
	m_enemyPokemon->setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(60.f, -15.f));
	updateHpBar(*m_enemyPokemon, m_enemyHpBar);
	m_enemyName.setFillColor(Color::Black);
	m_enemyName.setString(m_enemyPokemon->getName());
	m_enemyName.setPosition(m_enemyStatbar.getPosition() + Vector2f(6.f, -1.f));
	m_enemyLevel.setFillColor(Color::Black);
	m_enemyLevel.setString("Lv" + to_string(m_enemyPokemon->getLevel()));
	m_enemyLevel.setPosition(m_enemyStatbar.getPosition() + Vector2f(66.f, -1.f));
}


Battle::~Battle()
{
}

void Battle::initBattle(int battleType)
{
	// initialize battle
	m_screen.setTexture(Resource::texture("battle"));
	battleArenaLoader(battleType);
	// initialize menu background
	m_menuBg.setTexture(Resource::texture("battle_menu_bg"), true);
	m_menuBg.setOrigin(m_menuBg.getGlobalBounds().width, m_menuBg.getGlobalBounds().height);
	m_menuBg.setPosition(Vector2f(m_view.getCenter().x + (m_view.getSize().x / 2.f), m_view.getCenter().y + (m_view.getSize().y / 2.f)));
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
	// choose player pokemon
	m_currPokemon = getFirstAlivePokemon(m_player);
	if (m_currPokemon != -1)
		choosePokemon(true, m_currPokemon);
	else
		m_active = false;
	// initialize menu
	m_menu.addCommand("Fight", make_unique<FightCommand>(m_view, m_subScreen, m_playerPokemon, m_playerUsedAbility));
	m_menu.addCommand("Bag", nullptr);
	m_menu.addCommand("Pokemon", make_unique<PokemonListCommand>(m_subScreen, m_player, m_nextPokemon, true));
	m_menu.addCommand("Run", make_unique<ExitCommand>(&*this));
	m_menu.setOrigin(BOTTOM_RIGHT);
	m_menu.setPosition(Vector2f(m_view.getCenter().x + m_view.getSize().x / 2.f, m_view.getCenter().y + m_view.getSize().y / 2.f));
	// initialize player texts
	m_playerName.setFillColor(Color::Black);
	m_playerName.setPosition(m_playerStatbar.getPosition() + Vector2f(15.f, -1.f));
	m_playerLevel.setFillColor(Color::Black);
	m_playerLevel.setPosition(m_playerStatbar.getPosition() + Vector2f(75.f, -1.f));
	m_playerHP.setFillColor(Color::Black);
	m_playerHP.setPosition(m_playerStatbar.getPosition() + Vector2f(62.f, 17.f));
}

void Battle::draw(RenderWindow & window)
{
	if (!m_active)
		return;
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
	m_playerPokemon->draw(window);
	m_enemyPokemon->draw(window);
	playTurns(window);
	m_menu.draw(window);
	if (m_subScreen)
	{
		if (!m_subScreen->isActive())
		{
			m_subScreen.reset();
			window.setView(m_view);
		}
		else
			m_subScreen->draw(window);
	}
	else
		window.setView(m_view);
	if (m_msg)
	{
		if (!m_msg->isActive())
			m_msg.reset();
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
		if (m_currPokemon != m_nextPokemon)
		{
			auto next = m_player.begin() + m_nextPokemon;
			if (!(*next)->isDead())
			{
				m_currPokemon = m_nextPokemon;
				choosePokemon(true, m_currPokemon);
				m_subScreen.reset();
			}
		}
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

void Battle::updateHpBar(Pokemon & pokemon, Sprite & bar)
{
	bar.setTextureRect(pokemon.getHpBar().getTextureRect());
	m_playerHP.setString(to_string(m_playerPokemon->getHp()) + "/" + to_string(m_playerPokemon->getMaxHp()));
}

bool Battle::printMessage(const string & msg)
{
	static bool msgPrinted = false;
	if (!msgPrinted)
	{
		m_msg = make_unique<Chat>(Resource::texture("battle_menu_bg"), m_view, msg, Color::White);
		msgPrinted = true;
		return false;
	}
	else if (msgPrinted && !m_msg)
	{
		msgPrinted = false;
		return true;
	}
	return false;
}

int Battle::getFirstAlivePokemon(Trainer & trainer)
{
	int index = 0;
	auto pokemon = (*(trainer.cbegin() + index));
	while (pokemon->isDead())
	{
		++index;
		pokemon = (*(trainer.cbegin() + index));
	}
	if (trainer.cbegin() + index == trainer.cend())
		return -1;
	else
		return index;
}

void Battle::choosePokemon(bool isPlayer, int index)
{
	if (isPlayer)
	{
		m_playerPokemon = *(m_player.begin() + index);
		m_playerPokemon->setTexture("back");
		m_playerPokemon->setOrigin(BOTTOM_MIDDLE);
		m_playerPokemon->setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(-55.f, 32.f));
		updateHpBar(*m_playerPokemon, m_playerHpBar);
		updateExpBar();
		m_playerName.setString(m_playerPokemon->getName());
		m_playerLevel.setString("Lv" + to_string(m_playerPokemon->getLevel()));
		m_playerHP.setString(to_string(m_playerPokemon->getHp()) + "/" + to_string(m_playerPokemon->getMaxHp()));
	}
	else
	{
		m_enemyPokemon = *(m_enemy->begin() + index);
		m_enemyPokemon->setTexture("front");
		m_enemyPokemon->setOrigin(BOTTOM_MIDDLE);
		m_enemyPokemon->setPosition(Vector2f(m_view.getCenter().x, m_view.getCenter().y) + Vector2f(60.f, -15.f));
		updateHpBar(*m_enemyPokemon, m_enemyHpBar);
		m_enemyName.setString(m_enemyPokemon->getName());
		m_enemyLevel.setString("Lv" + to_string(m_enemyPokemon->getLevel()));
	}
}

void Battle::playTurns(RenderWindow & window)
{
	playerDeadHandler();
	enemyDeadHandler();
	if (m_playerUsedAbility)	// if an ability was used
	{
		if (m_playerTurnExec && m_enemyTurnExec)
		{
			m_enemyUsedAbility = m_enemyPokemon->getRandAbility();

			if (m_playerUsedAbility->getSpeed() > m_enemyUsedAbility->getSpeed())	// player ability faster than enemy
				m_isPlayerTurn = true;
			else if (m_enemyUsedAbility->getSpeed() > m_playerUsedAbility->getSpeed())	// enemy ability faster than player
				m_isPlayerTurn = false;
			else
			{
				bool random = rand() % 2;
				m_isPlayerTurn = random;
			}

			m_playerTurnExec = m_enemyTurnExec = false;
		}
		if (m_isPlayerTurn)
			execPlayerTurn(window);
		else
			execEnemyTurn(window);
		if (m_playerTurnExec && m_enemyTurnExec)
			m_playerUsedAbility = m_enemyUsedAbility = nullptr;
	}
}

void Battle::execPlayerTurn(RenderWindow & window)
{
	m_playerUsedAbility->setOrigin(BOTTOM_MIDDLE);
	m_playerUsedAbility->setPosition(m_enemyPokemon->getPosition());
	m_playerUsedAbility->draw(window);
	if (printMessage(m_playerPokemon->getName() + " used " + m_playerUsedAbility->getName()))
	{
		float lvlDiff = float(m_playerPokemon->getLevel()) / float(m_enemyPokemon->getLevel());
		m_playerUsedAbility->use(m_enemyPokemon, lvlDiff);
		updateHpBar(*m_enemyPokemon, m_enemyHpBar);
		m_playerTurnExec = true;
		m_isPlayerTurn = false;
	}
}

void Battle::execEnemyTurn(RenderWindow & window)
{
	m_enemyUsedAbility->setOrigin(BOTTOM_MIDDLE);
	m_enemyUsedAbility->setPosition(m_playerPokemon->getPosition());
	m_enemyUsedAbility->draw(window);
	if (printMessage("Enemy " + m_enemyPokemon->getName() + " used " + m_enemyUsedAbility->getName()))
	{
		float lvlDiff = float(m_enemyPokemon->getLevel()) / float(m_playerPokemon->getLevel());
		m_enemyUsedAbility->use(m_playerPokemon, lvlDiff);
		updateHpBar(*m_playerPokemon, m_playerHpBar);
		m_enemyTurnExec = true;
		m_isPlayerTurn = true;
	}
}

void Battle::playerDeadHandler()
{
	if (m_playerPokemon->isDead())
	{
		if (!m_player.isDefeated())		// if the player still has pokemons alive
		{
			m_playerTurnExec = m_enemyTurnExec = true;
			m_playerUsedAbility = nullptr;
			if (!m_subScreen && printMessage(m_playerPokemon->getName() + " fainted! use next Pokemon?"))
			{
				auto boolMenu = make_unique<Menu>(Resource::texture("boolean_menu"), Vector2f(1.f, 2.f), false);
				boolMenu->addCommand("Yes", make_unique<PokemonListCommand>(m_subScreen, m_player, m_nextPokemon, true));
				boolMenu->addCommand("No", make_unique<ExitCommand>(&*this));
				boolMenu->setOrigin(BOTTOM_RIGHT);
				boolMenu->setPosition(Vector2f(m_view.getCenter() + Vector2f(m_view.getSize().x / 2.f, 32.f)));
				m_subScreen = std::move(boolMenu);
			}
		}
		else	// the player doesn't have more alive pokemons
		{
			if (printMessage("You are out of useable Pokemons! Go to the pharmacy to heal your Pokemons."))
				m_active = false;
		}
	}
}

void Battle::enemyDeadHandler()
{
	if (m_enemyPokemon->isDead())
	{
		m_playerTurnExec = m_enemyTurnExec = true;
		m_playerUsedAbility = nullptr;
		if (!m_expAdded)
			addExp();
		else
		{
			if (m_enemy)	// if fighting vs trainer
			{
				if (!m_enemy->isDefeated())
				{
					++m_enemyCurrPokemon;
					choosePokemon(false, m_enemyCurrPokemon);
					m_expAdded = false;
				}
				else	// if enemy out of useable pokemons
				{
					if (printMessage("You won the battle!"))
						m_active = false;
				}
			}
			else			// if fighting vs wild pokemon
			{
				if (printMessage("Wild " + m_enemyPokemon->getName() + " fainted!"))
					m_active = false;
			}
		}
	}
}

void Battle::addExp()
{
	float lvlDiff = float(m_enemyPokemon->getLevel()) / float(m_playerPokemon->getLevel());
	int amount = int(BASE_EXP * lvlDiff);
	if (printMessage(m_playerPokemon->getName() + " gained " + to_string(amount) + " EXP!"))
	{
		m_playerPokemon->addExp(amount);
		updateExpBar();
		m_expAdded = true;
	}
}

void Battle::updateExpBar()
{
	m_expBar.setTextureRect(m_playerPokemon->getExpBar().getTextureRect());
	m_playerLevel.setString("Lv" + to_string(m_playerPokemon->getLevel()));
	updateHpBar(*m_playerPokemon, m_playerHpBar);
}

