#pragma once
#include "GameObject.h"
#include "Utils.h"

class Pokemon; //define pokemon class 

using std::string;
using std::shared_ptr;
using sf::Sprite;
using sf::Vector2f;

enum Element  //elements enum for abilities and pokemon types
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

class Ability : public GameObject //Inherit from GameObject
{
public:
	Ability(const string & name, const string & element, int damage, int speed); //constructor
	~Ability(); //destructor

	static Element stringToElement(const string & x); //converting string to enum element

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

	//set functions for the sprites
	void setPosition(const Vector2f & pos) { m_sprite.setPosition(pos); }
	void setOrigin(SPOT spot) { Utils::setOrigin(m_sprite, spot); }

	//use function
	void use(shared_ptr<Pokemon> enemy, float lvlDiff);

private:
	int elementAdvantage(Element enemyElement) const; //element advantage private class
													  //to make adventage between diff elemets
	string m_name; //Ability name member
	Sprite m_sprite; //sprite member
	Element m_element; //Ability element member
	int m_damage; //ability damage member
	int m_speed; //ability speed member
};

