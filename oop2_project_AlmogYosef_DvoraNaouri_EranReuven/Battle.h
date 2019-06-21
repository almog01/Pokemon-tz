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
	// 2 types of c-tors: battle vs trainer / battle vs wild pokemon
	Battle(Player & player, Trainer & enemy, shared_ptr<Music> music);
	Battle(Player & player, Pokemon & wildPokemon, shared_ptr<Music> music);
	~Battle();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;
	
private:
	// initializes battle
	void initBattle();

	// updates hpbar 
	void updateHpBar(Pokemon & pokemon, Sprite & bar);

	// prints a message, returns true when message was read (user pressed "z")
	bool printMessage(const string & msg);

	// returns the index of the first alive pokemon of a trainer
	int getFirstAlivePokemon(Trainer & trainer);

	// changes the chosen pokemon of a player / enemy
	void choosePokemon(bool isPlayer, int index);

	// plays the turn of the player and and the enemy
	void playTurns(RenderWindow & window);

	// executes the player turn
	void execPlayerTurn(RenderWindow & window);
	// executes the enemy turn
	void execEnemyTurn(RenderWindow & window);
	
	// handles the case when the player pokemon is dead
	void playerDeadHandler();
	// handles the case when the enemy pokemon is dead
	void enemyDeadHandler();

	// adds exp to the player's pokemon
	void addExp();

	// updates exp bar
	void updateExpBar();

	shared_ptr<Music> m_music;	// battle music
	sf::View m_view;			// battle view
	Sprite m_menuBg;			// menu background
	Sprite m_playerStatbar;		// player statbar
	Sprite m_playerHpBar;		// player hpbar
	Sprite m_expBar;			// exp bar
	Sprite m_enemyStatbar;		// enemy statbar
	Sprite m_enemyHpBar;		// enemy hpbar
	Text m_playerName;			// player name text
	Text m_playerLevel;			// player level text
	Text m_playerHP;			// player hp text
	Text m_enemyName;			// enemy name text
	Text m_enemyLevel;			// enemy level text
	Menu m_menu;				// bottom menu
	Player & m_player;			// reference to the player
	Trainer * m_enemy = nullptr;// pointer to the enemy
	shared_ptr<Pokemon> m_playerPokemon;		// chosen player pokemon
	shared_ptr<Pokemon> m_enemyPokemon;			// chosen enemy pokemon
	unique_ptr<Screen> m_subScreen = nullptr;	// pointer to sub-screen: pokemon-list, fight-command...
	Ability* m_playerUsedAbility = nullptr;		// chosen player ability
	Ability* m_enemyUsedAbility = nullptr;		// chosen enemy ability
	bool m_isPlayerTurn = false;				// player or enemy turn flag
	bool m_playerTurnExec = true;				// player executed his turn flag
	bool m_enemyTurnExec = true;				// enemy executed his turn flag
	unique_ptr<Chat> m_msg = nullptr;			// pointer to a message
	int m_currPokemon = 0;						// current player's selected pokemon index
	int m_nextPokemon = 0;						// next player's selected pokemon index
	int m_enemyCurrPokemon = 0;					// current enemy's selected pokemon index
	bool m_expAdded = false;					// exp added flag
};

