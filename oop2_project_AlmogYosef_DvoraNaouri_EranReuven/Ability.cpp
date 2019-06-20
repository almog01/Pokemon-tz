#include "Ability.h"
#include "Pokemon.h"

const int ELEMENT_BONUS = 20;

Ability::Ability(const string & name, const string & element, int damage, int speed)
	: m_sprite(Resource::texture(element + "_ability")), m_element(stringToElement(element)), m_damage(damage), m_speed(speed)
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
	if (x == "ELECTRIC")
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
	else if (x == "PSYCHIC")
		return PSYCHIC;
	else
		return NORMAL;
}

void Ability::use(shared_ptr<Pokemon> enemy, float lvlDiff)
{
	Element enemyElement = enemy->getElement();
	int finalDamage = int(lvlDiff * m_damage) + elementAdvantage(enemyElement);
	enemy->setHp(enemy->getHp() - finalDamage);
}

int Ability::elementAdvantage(Element enemyElement) const
{
	switch (m_element)
	{
	case ELECTRIC:
		switch (enemyElement)
		{
		case WATER:
		case FLYING:
			return ELEMENT_BONUS;
		case ELECTRIC:
		case GRASS:
			return -ELEMENT_BONUS;
		default:
			return 0;
		}
		return 0;
	case GROUND:
		switch (enemyElement)
		{
		case FIRE:
		case ELECTRIC:
			return ELEMENT_BONUS;
		case GRASS:
		case GROUND:
			return -ELEMENT_BONUS;
		default:
			return 0;
		}
		break;
	case FIRE:
		switch (enemyElement)
		{
		case GRASS:
		case PSYCHIC:
			return ELEMENT_BONUS;
		case FIRE:
		case WATER:
			return -ELEMENT_BONUS;
		default:
			return 0;
		}
		break;
	case WATER:
		switch (enemyElement)
		{
		case FIRE:
		case GROUND:
			return ELEMENT_BONUS;
		case GRASS:
		case WATER:
			return -ELEMENT_BONUS;
		default:
			return 0;
		}
		return 0;
	case FLYING:
		switch (enemyElement)
		{
		case GRASS:	
		case NORMAL:
			return ELEMENT_BONUS;
		case ELECTRIC:
		case FLYING:
			return -ELEMENT_BONUS;
		default:
			return 0;
		}
		return 0;
	case GRASS:
		switch (enemyElement)
		{
		case WATER:
		case GROUND:
			return ELEMENT_BONUS;
		case FIRE:
		case FLYING:
			return -ELEMENT_BONUS;
		default:
			return 0;
		}
		return 0;
	case PSYCHIC:
		switch (enemyElement)
		{
		case FLYING:
		case ELECTRIC:
			return ELEMENT_BONUS;
		case GROUND:
		case PSYCHIC:
			return -ELEMENT_BONUS;
		default:
			return 0;
		}
	case NORMAL:
		return 0;
	default:
		return 0;
	}
	return 0;
}

void Ability::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
