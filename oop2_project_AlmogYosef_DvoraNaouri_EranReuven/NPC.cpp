#include "NPC.h"
#include "Player.h"


NPC::NPC(const string & name)
{
	m_sprite.setTexture(Resource::texture(name), true);
	//m_sprite.setTextureRect(sf::IntRect(16, 0, 16, 19));
}


NPC::~NPC()
{
}

void NPC::handleCollision(Collider & collider)
{
	collider.handleCollision(*this);
}

void NPC::handleCollision(Player & player)
{
	player.handleCollision(*this);
}

void NPC::handleCollision(NPC & npc)
{
}

void NPC::handleCollision(Pokemon & pokemon)
{
}

void NPC::handleCollision(Door & door)
{
}
