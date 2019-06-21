#pragma once
#include "NPC.h"
class SpecialNPC : public NPC // Inherit from NPC
{
public:
	SpecialNPC(const string & name); //constructor
	virtual ~SpecialNPC(); //destructor 
};

