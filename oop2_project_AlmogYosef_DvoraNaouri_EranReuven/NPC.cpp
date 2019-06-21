#include "NPC.h"
#include "Player.h"
#include "Chat.h"

using std::make_unique;

NPC::NPC(const string & name)
{
	m_sprite.setTexture(Resource::texture(name), true);
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

void NPC::handleCollision(Door & door)
{
}

void NPC::startChat(unique_ptr<Screen>& screen, const View & view) const
{
	screen = make_unique<Chat>(Resource::texture("chat_window"), view, m_chat);
}
