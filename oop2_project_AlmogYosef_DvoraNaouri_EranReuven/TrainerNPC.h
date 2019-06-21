#pragma once
#include "NPC.h"
#include "Trainer.h"
class TrainerNPC : public NPC, public Trainer //Inherit from NPC and from Trainer
{
public:
	TrainerNPC(const string & name); //constructor
	~TrainerNPC(); //destructor
};

