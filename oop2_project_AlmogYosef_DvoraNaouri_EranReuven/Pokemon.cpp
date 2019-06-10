#include "Pokemon.h"
#include "Resource.h"


Pokemon::Pokemon(const string & name)
	: m_back(Resource::texture(name + "_back")), m_front(Resource::texture(name + "_front")), m_icon(Resource::texture(name + "_icon"))
{
}

void Pokemon::setTexture(const string & type)
{
	if (type == "front")
		m_sprite.setTexture(m_front);
	else if(type == "back")
		m_sprite.setTexture(m_back);	
	else if(type == "icon")
		m_sprite.setTexture(m_icon);
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

Pokemon::~Pokemon()
{
}
