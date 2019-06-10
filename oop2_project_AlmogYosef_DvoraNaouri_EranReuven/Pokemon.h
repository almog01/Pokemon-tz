#pragma once
#include "Character.h"
#include "Move.h"


enum xyzPokemon{pikachu, charmander, bulbasaur, squirtle};


class Move;

class Pokemon : public Character
{
public:
	//default constructor
	Pokemon(const string & name);
	//default copy constructor
	Pokemon(const Pokemon&) = default;
	//set Texture for present sprite
	void setTexture(const string & type);

	//functions to set and get pokemon stats, elements
	void setLevel(int level) { m_level = level; }
	int getLevel() { return m_level; }
	Pokemon& setHp(int hp) { m_hp = hp; return *this; }
	int getHp() { return m_hp; }
	Pokemon& setMaxHp(int maxhp) { m_maxHp = maxhp; return *this; }
	int getMaxHp() { return m_maxHp; }
	void setXp(int xp) { m_xp = xp; }
	int getXp() { return m_xp; }
	void setElement(Element element) { m_elements.push_back(element); }
	vector<Element> &getElement() { return m_elements; }
	
	//pokemon moves
	//void setMove(unique_ptr<Move> & x) { m_moves.push_back(std::move(x)); }

	//fly type
	Pokemon& setCanFly(bool x) { m_flyingtype = x; return *this; }
	bool getCanFly() { return m_flyingtype; }

	//pokemon condition get and set
	void setIsStun(bool x) { is_stun = x; }
	bool getIsStun() { return is_stun; }

	void setIsSleep(bool x) { is_sleep = x; }
	bool getIsSleep(bool x) { return is_sleep; }


	// Inherited via Character
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Pokemon & pokemon) override;
	virtual void handleCollision(Door & door) override;

	~Pokemon();

private:
	//pokemon textures
	const sf::Texture &m_front;
	const sf::Texture &m_back;
	const sf::Texture &m_icon;

	//pokemon moves
	//vector<std::unique_ptr<Move>> m_moves;

	//pokemon stats
	int m_level = 2;
	int m_hp;
	int m_maxHp;
	int m_xp = 0;

	//pokemon elements
	vector<Element> m_elements;

	//pokemon condition
	bool is_stun = false;
	bool is_sleep = false;
	bool is_fade = false;
	
	//fly pokemon type
	bool m_flyingtype = false;


};
//const monster pikachu = {
//"pikachu",
//&tackle,
//&tailwhip,
//&thundershock,
//&roar,
//element::N_A,
//element::ELECTRIC,
//5,
//110,
//110,
//0,
//false
//};
