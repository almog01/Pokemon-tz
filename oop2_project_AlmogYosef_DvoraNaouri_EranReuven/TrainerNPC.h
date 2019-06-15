#pragma once
#include "NPC.h"
#include "Trainer.h"
class TrainerNPC : public NPC, public Trainer
{
public:
	TrainerNPC(const string & name);
	~TrainerNPC();
};

