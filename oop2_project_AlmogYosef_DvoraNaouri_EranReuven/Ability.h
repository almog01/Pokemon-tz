#pragma once
#include "GameObject.h"
#include "Utils.h"

class Pokemon;

using std::string;
using std::shared_ptr;
using sf::Sprite;
using sf::Vector2f;

enum Element 
{
	NORMAL,
	ELECTRIC,
	GROUND,
	FIRE,
	WATER,
	FLYING,
	GRASS,
	PSYCHIC
};

class Ability : public GameObject
{
public:
	Ability(const string & name, const string & element, int damage, int speed);
	~Ability();

	static Element stringToElement(const string & x);

	// Inherited via GameObject
	virtual void draw(sf::RenderWindow &window);

	//set and get function for ability members
	void setElement(Element element) { m_element = element; }
	Element getElement() { return m_element; }
	void setDmg(int dmg) { m_damage = dmg; }
	int getDmg() { return m_damage; }
	void setSpeed(int speed) { m_speed = speed; }
	int getSpeed() { return m_speed; }
	string getName() { return m_name; }

	void setPosition(const Vector2f & pos) { m_sprite.setPosition(pos); }
	void setOrigin(SPOT spot) { Utils::setOrigin(m_sprite, spot); }

	void use(shared_ptr<Pokemon> enemy, float lvlDiff);

private:
	int elementAdvantage(Element enemyElement) const;

	string m_name;
	Sprite m_sprite;
	Element m_element;
	int m_damage;
	int m_speed;
};

