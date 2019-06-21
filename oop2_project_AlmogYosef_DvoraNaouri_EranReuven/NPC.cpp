#include "NPC.h"
#include "Player.h"
#include "Chat.h"

using std::make_unique;

NPC::NPC(const string & name) //constructor gets npc name reference
{
	m_sprite.setTexture(Resource::texture(name), true); //loading the sprite via name
}


NPC::~NPC() //destructor
{
}
/*Coliders handlers functions (Double dispatch)*/
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
/*End of Coliders handlers functions (Double dispatch)*/

//start chat function will gets reference for the screen and the view
void NPC::startChat(unique_ptr<Screen>& screen, const View & view) const
{
	//drawing the chat window
	screen = make_unique<Chat>(Resource::texture("chat_window"), view, m_chat);
}
