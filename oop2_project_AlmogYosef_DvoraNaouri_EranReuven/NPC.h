#pragma once
#include "Character.h"
#include "Screen.h"

using std::string;
using std::unique_ptr;
using sf::View;

class NPC : public Character
{
public:
	NPC(const string & name);
	~NPC();

	// Inherited via Character
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Door & door) override;

	// Setter
	void setChat(const string & chat) { m_chat = chat; }

	virtual void startChat(unique_ptr<Screen> & screen, const View & view) const;

private:
	string m_chat;
};

