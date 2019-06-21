#include "Pokemon.h"
#include "Resource.h"

using std::toupper;
using sf::IntRect;

//constans values for the pokemon status
const float MAX_XP = 100;
const int LEVEL_UP_BONUS_HP = 7; 

//constructor will init name reference, level, textures
Pokemon::Pokemon(const string & name, int level)
	: m_back(Resource::texture(name + "_back")), m_front(Resource::texture(name + "_front")), m_icon(Resource::texture(name + "_icon")), m_level(level)
{
	m_name = name;
	m_name[0] = toupper(m_name[0]);	// convert first letter to uppercase
}

Pokemon::~Pokemon() //destructor
{
}

void Pokemon::setTexture(const string & type) //set pokemon texture
{
	if (type == "front")
		m_sprite.setTexture(m_front);
	else if (type == "back")
		m_sprite.setTexture(m_back);
	else if (type == "icon")
		m_sprite.setTexture(m_icon);
}

Pokemon & Pokemon::setLevel(int level) //set pokemon level
{
	int diff = level - m_level; //diff for status calculate
	for (int i = 0; i < diff; ++i)
		m_maxHp += LEVEL_UP_BONUS_HP;
	m_hp = m_maxHp;
	m_level = level;
	return *this;
}

Sprite Pokemon::getHpBar() const //get the hp bar
{
	//setting the hp bar
	Sprite bar(Resource::texture("battle_hpbar"));
	auto rect = bar.getTextureRect();
	static int rectWidth = rect.width;
	if (m_hp <= 0) //if the hp is 0 or low, its an empty bar
		bar.setTextureRect(IntRect(rect.left, rect.top, 0, rect.height));
	else //in any other case
		bar.setTextureRect(IntRect(rect.left, rect.top, int((float(m_hp) / float(m_maxHp)) * rectWidth), rect.height));
	return bar; //return the bar
}

Sprite Pokemon::getExpBar() const //get the exp bar
{
	//setting the exp bar
	Sprite bar(Resource::texture("battle_expbar"));
	auto rect = bar.getTextureRect();
	static int rectWidth = rect.width;
	if (m_xp <= 0) //if ex is 0 or low, its an empty bar
		bar.setTextureRect(IntRect(rect.left, rect.top, 0, rect.height));
	else //in any other case
		bar.setTextureRect(IntRect(rect.left, rect.top, int((float(m_xp) / MAX_XP) * rectWidth), rect.height));
	return bar; //return the bar
}

Ability * Pokemon::getAbility(int index) const //get a ability from the pokemon
{
	try //expectation for wrong index chose
	{
		return m_abilities.at(index);
	}
	catch (const std::out_of_range&)
	{
		return nullptr;
	}
}

/*get rand ability will get random ability for opponent pokemons*/
Ability * Pokemon::getRandAbility() const
{
	int index = rand() % m_abilities.size();
	return m_abilities[index];
}

void Pokemon::addExp(int amount) //add exp function (rewards for defeat)
{
	m_xp += amount;
	while (m_xp >= MAX_XP) //if pokemon got to the max xp level amount, level up.
	{
		m_level++;
		m_hp += LEVEL_UP_BONUS_HP;
		m_maxHp += LEVEL_UP_BONUS_HP;
		m_xp -= int(MAX_XP);
	}
}
/*Coliders handlers functions (Double dispatch)*/
void Pokemon::handleCollision(Collider & collider)
{
}

void Pokemon::handleCollision(Player & player)
{
}

void Pokemon::handleCollision(NPC & npc)
{
}

void Pokemon::handleCollision(Door & door)
{
}
