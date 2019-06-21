#pragma once
#include "SpecialNPC.h"
class NurseNPC : public SpecialNPC //Inherit from special NPC
{
public:
	NurseNPC(const string & name); //constructor
	~NurseNPC(); //destructor

	virtual void startChat(unique_ptr<Screen> & screen, const View & view) const override; //start chat func

	virtual FloatRect getGlobalBounds() const override; //get global bounds of sprite func
};

