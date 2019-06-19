#pragma once
#include "GameObject.h"

class Pokemon;

using std::string;
using std::shared_ptr;

enum Element {
	N_A, // Not applicable
	ELECTRIC,
	GROUND,
	FIRE,
	WATER,
	FLYING,
	GRASS,
	NORMAL
};

class Ability : public GameObject
{
public:
	Ability(const string & name, Element element, int damage, int speed);
	~Ability();

	// Inherited via GameObject
	virtual void draw(sf::RenderWindow &window);

	static Element stringToElement(const string & x);

	//set and get function for ability members
	void setElement(Element element) { m_element = element; }
	Element getElement() { return m_element; }
	void setDmg(int dmg) { m_damage = dmg; }
	int getDmg() { return m_damage; }
	void setSpeed(int speed) { m_speed = speed; }
	int getSpeed() { return m_speed; }
	string getName() { return m_name; }

	void use(shared_ptr<Pokemon> enemy, float lvlDiff);

private:
	string m_name;
	Element m_element;
	int m_damage;
	int m_speed;
};

