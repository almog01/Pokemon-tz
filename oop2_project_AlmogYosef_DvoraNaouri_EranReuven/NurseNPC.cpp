#include "NurseNPC.h"
#include "Player.h"


//constructor init the NPC name
NurseNPC::NurseNPC(const string & name) : SpecialNPC(name)
{
}


NurseNPC::~NurseNPC() //destructor
{
}

void NurseNPC::startChat(unique_ptr<Screen>& screen, const View & view) const
{
	SpecialNPC::startChat(screen, view); //using father class start chat function
	
	//nurse npc action ->heal player's pokemons
	for (auto it = Player::instance().begin(); it != Player::instance().end(); ++it)
		(*it)->setHp((*it)->getMaxHp());
}

FloatRect NurseNPC::getGlobalBounds() const //get global bounds of the sprite
{
	FloatRect bounds = SpecialNPC::getGlobalBounds(); //gets from father class
	bounds.height *= 3; //make the boudes bigger for the nurse position
	return bounds; //return the bounds
}
