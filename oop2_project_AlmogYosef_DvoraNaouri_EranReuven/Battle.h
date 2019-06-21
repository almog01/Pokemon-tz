#pragma once
#include "Screen.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Player.h"
#include "Menu.h"
#include "Chat.h"

using std::unique_ptr;
using std::shared_ptr;
using sf::Text;

class Battle : public Screen
{
public:
	Battle(Player & player, Trainer & enemy, shared_ptr<Music> music);
	Battle(Player & player, Pokemon & wildPokemon, shared_ptr<Music> music);
	~Battle();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;
	
private:
	void initBattle();
	void updateHpBar(Pokemon & pokemon, Sprite & bar);
	bool printMessage(const string & msg);
	int getFirstAlivePokemon(Trainer & trainer);
	void choosePokemon(bool isPlayer, int index);
	void playTurns(RenderWindow & window);
	void execPlayerTurn(RenderWindow & window);
	void execEnemyTurn(RenderWindow & window);
	void playerDeadHandler();
	void enemyDeadHandler();
	void addExp();
	void updateExpBar();

	shared_ptr<Music> m_music;
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
	Player & m_player;
	Trainer * m_enemy = nullptr;
	shared_ptr<Pokemon> m_playerPokemon;
	shared_ptr<Pokemon> m_enemyPokemon;
	unique_ptr<Screen> m_subScreen = nullptr;
	Ability* m_playerUsedAbility = nullptr;
	Ability* m_enemyUsedAbility = nullptr;
	bool m_isPlayerTurn = false;			// player or enemy turn flag
	bool m_playerTurnExec = true;
	bool m_enemyTurnExec = true;
	unique_ptr<Chat> m_msg = nullptr;
	int m_currPokemon = 0;
	int m_nextPokemon = 0;
	int m_enemyCurrPokemon = 0;
	bool m_expAdded = false;
};

