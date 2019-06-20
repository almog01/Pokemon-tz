#pragma once
#include "SpecialNPC.h"
class NurseNPC : public SpecialNPC
{
public:
	NurseNPC(const string & name);
	~NurseNPC();

	virtual void startChat(unique_ptr<Screen> & screen, const View & view) const override;

	virtual FloatRect getGlobalBounds() const override;
};

