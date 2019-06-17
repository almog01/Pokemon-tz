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
	void setLevel(int level) { m_level = level; }
	int getLevel() const { return m_level; }
	Pokemon& setHp(int hp) { m_hp = (hp > 0) ? hp : 0; return *this; }
	int getHp() const { return m_hp; }
	Sprite getHpBar() const;
	Pokemon& setMaxHp(int maxhp) { m_maxHp = maxhp; return *this; }
	int getMaxHp() const { return m_maxHp; }
	void setXp(int xp) { m_xp = xp; }
	int getXp() const { return m_xp; }
	void setElement(Element element) { m_elements.push_back(element); }
	vector<Element> &getElement() { return m_elements; }
	Ability* getAbility(int index) const;
	Ability* getRandAbility() const;
	string getName() const { return m_name; }
	const Texture & getIcon() { return m_icon; }
	void setOrigin(SPOT spot) { Utils::setOrigin(m_sprite, spot); }

	//add ability
	void addAbility(Ability* x) { m_abilities.push_back(x); }

	//fly type
	Pokemon& setCanFly(bool x) { m_flyingtype = x; return *this; }
	bool getCanFly() const { return m_flyingtype; }

	//pokemon condition get and set
	void setIsStun(bool x) { is_stun = x; }
	bool getIsStun() const { return is_stun; }

	void setIsSleep(bool x) { is_sleep = x; }
	bool getIsSleep(bool x) const { return is_sleep; }

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

	//pokemon elements
	vector<Element> m_elements;

	//pokemon condition
	bool is_stun = false;
	bool is_sleep = false;
	bool is_fade = false;

	//fly pokemon type
	bool m_flyingtype = false;
};

