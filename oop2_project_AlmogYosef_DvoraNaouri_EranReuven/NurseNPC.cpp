#include "NurseNPC.h"
#include "Player.h"


NurseNPC::NurseNPC(const string & name) : SpecialNPC(name)
{
}


NurseNPC::~NurseNPC()
{
}

void NurseNPC::startChat(unique_ptr<Screen>& screen, const View & view) const
{
	SpecialNPC::startChat(screen, view);
	
	Player::instance().healPokemons();
}

FloatRect NurseNPC::getGlobalBounds() const
{
	FloatRect bounds = SpecialNPC::getGlobalBounds();
	bounds.height *= 3;
	return bounds;
}
