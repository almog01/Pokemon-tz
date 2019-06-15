#include "Ability.h"
#include "Pokemon.h"


Ability::Ability(const string & name, Element element, int damage, int speed)
	: m_element(element), m_damage(damage), m_speed(speed)
{
	m_name = name;
	// find and replace '_' character with ' ' in the ability name
	string toReplace("_");
	size_t pos = m_name.find(toReplace);
	if (pos != std::string::npos)	// if sub-string found
		m_name.replace(pos, toReplace.length(), " ");
}


Ability::~Ability()
{
}

Element Ability::stringToElement(const string & x)
{
	if (x == "N_A")
		return N_A;
	else if (x == "ELECTRIC")
		return ELECTRIC;
	else if (x == "GROUND")
		return GROUND;
	else if (x == "FIRE")
		return FIRE;
	else if (x == "WATER")
		return WATER;
	else if (x == "FLYING")
		return FLYING;
	else if (x == "GRASS")
		return GRASS;
	else if (x == "NORMAL")
		return NORMAL;
	else
		return N_A;
}

void Ability::use(shared_ptr<Pokemon> enemy)
{
	enemy->setHp(enemy->getHp() - m_damage);
}

void Ability::draw(sf::RenderWindow &window)
{
}
