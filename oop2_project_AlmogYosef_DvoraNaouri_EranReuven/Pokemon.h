#pragma once
#include "Character.h"
#include "Ability.h"
#include "Utils.h"

using std::string;
using std::vector;
using std::unique_ptr;
using sf::Sprite;

class Pokemon : public Character
{
public:
	Pokemon(const string & name);
	~Pokemon();

	//set Texture for present sprite
	void setTexture(const string & type);

	//functions to set and get pokemon stats, elements
	Pokemon& setLevel(int level) { m_level = level; return *this; }
	int getLevel() const { return m_level; }
	Pokemon& setHp(int hp) { m_hp = (hp > 0) ? hp : 0; return *this; }
	int getHp() const { return m_hp; }
	Sprite getHpBar() const;
	Sprite getExpBar() const;
	Pokemon& setMaxHp(int maxhp) { m_maxHp = maxhp; return *this; }
	int getMaxHp() const { return m_maxHp; }
	Pokemon& setXp(int xp) { m_xp = xp; return *this; }
	int getXp() const { return m_xp; }
	Pokemon& setElement(const string & element) { m_element = Ability::stringToElement(element); return *this; }
	Element getElement() const { return m_element; }
	Ability* getAbility(int index) const;
	Ability* getRandAbility() const;
	string getName() const { return m_name; }
	const Texture & getIcon() { return m_icon; }
	void setOrigin(SPOT spot) { Utils::setOrigin(m_sprite, spot); }
	bool isDead() const { return m_hp == 0; }

	//add functions
	void addAbility(Ability* x) { m_abilities.push_back(x); }
	void addExp(int amount);

	// Inherited via Character
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Pokemon & pokemon) override;
	virtual void handleCollision(Door & door) override;

private:
	//pokemon name
	string m_name;

	//pokemon textures
	const sf::Texture &m_front;
	const sf::Texture &m_back;
	const sf::Texture &m_icon;

	//pokemon abilities
	vector<Ability*> m_abilities;

	//pokemon stats
	int m_level = 2;
	int m_hp;
	int m_maxHp;
	int m_xp = 0;

	//pokemon element
	Element m_element;
};

