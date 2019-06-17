#pragma once
#include "Screen.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Menu.h"
#include "Chat.h"

using std::unique_ptr;
using std::shared_ptr;
using sf::Text;

class Battle : public Screen
{
public:
	Battle(Trainer & player, Trainer & enemy, int battleType = 1);
	~Battle();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;
	
	void battleArenaLoader(int battleType);


private:
	void choosePokemon(bool isPlayer, int index);
	void execPlayerTurn();
	void execEnemyTurn();

	sf::View m_view;
	Sprite m_menuBg;		// menu background
	Sprite m_playerStatbar;	// player statbar
	Sprite m_playerHpBar;
	Sprite m_expBar;
	Sprite m_enemyStatbar;	// enemy statbar
	Sprite m_enemyHpBar;
	Text m_playerName;
	Text m_playerLevel;
	Text m_playerHP;
	Text m_enemyName;
	Text m_enemyLevel;
	Menu m_menu;
	Trainer & m_player;
	Trainer & m_enemy;
	vector<shared_ptr<Pokemon>>::iterator m_playerPokemon;
	vector<shared_ptr<Pokemon>>::iterator m_enemyPokemon;
	unique_ptr<Screen> m_subScreen = nullptr;
	//shared_ptr<Pokemon> m_playerPokemon;
	//shared_ptr<Pokemon> m_enemyPokemon;
	Ability* m_playerUsedAbility = nullptr;
	bool m_isPlayerTurn = true;			// player or enemy turn flag
	unique_ptr<Chat> m_msg = nullptr;
};

