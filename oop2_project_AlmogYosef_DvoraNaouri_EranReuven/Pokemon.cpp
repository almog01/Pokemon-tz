#include "Pokemon.h"
#include "Resource.h"

using std::toupper;
using sf::IntRect;

const float MAX_XP = 100;
const int LEVEL_UP_BONUS_HP = 7;

Pokemon::Pokemon(const string & name)
	: m_back(Resource::texture(name + "_back")), m_front(Resource::texture(name + "_front")), m_icon(Resource::texture(name + "_icon"))
{
	m_name = name;
	m_name[0] = toupper(m_name[0]);	// convert first letter to uppercase
}

Pokemon::~Pokemon()
{
}

void Pokemon::setTexture(const string & type)
{
	if (type == "front")
		m_sprite.setTexture(m_front);
	else if (type == "back")
		m_sprite.setTexture(m_back);
	else if (type == "icon")
		m_sprite.setTexture(m_icon);
}

Sprite Pokemon::getHpBar() const
{
	Sprite bar(Resource::texture("battle_hpbar"));
	auto rect = bar.getTextureRect();
	static int rectWidth = rect.width;
	if (m_hp <= 0)
		bar.setTextureRect(IntRect(rect.left, rect.top, 0, rect.height));
	else
		bar.setTextureRect(IntRect(rect.left, rect.top, int((float(m_hp) / float(m_maxHp)) * rectWidth), rect.height));
	return bar;
}

Sprite Pokemon::getExpBar() const
{
	Sprite bar(Resource::texture("battle_expbar"));
	auto rect = bar.getTextureRect();
	static int rectWidth = rect.width;
	if (m_xp <= 0)
		bar.setTextureRect(IntRect(rect.left, rect.top, 0, rect.height));
	else
		bar.setTextureRect(IntRect(rect.left, rect.top, int((float(m_xp) / MAX_XP) * rectWidth), rect.height));
	return bar;
}

Ability * Pokemon::getAbility(int index) const
{
	try
	{
		return m_abilities.at(index);
	}
	catch (const std::out_of_range&)
	{
		return nullptr;
	}
}

Ability * Pokemon::getRandAbility() const
{
	int index = rand() % m_abilities.size();
	return m_abilities[index];
}

void Pokemon::addExp(int amount)
{
	m_xp += amount;
	while (m_xp >= MAX_XP)
	{
		m_level++;
		m_hp += LEVEL_UP_BONUS_HP;
		m_maxHp += LEVEL_UP_BONUS_HP;
		m_xp -= int(MAX_XP);
	}
}

void Pokemon::handleCollision(Collider & collider)
{
}

void Pokemon::handleCollision(Player & player)
{
}

void Pokemon::handleCollision(NPC & npc)
{
}

void Pokemon::handleCollision(Pokemon & pokemon)
{
}

void Pokemon::handleCollision(Door & door)
{
}
