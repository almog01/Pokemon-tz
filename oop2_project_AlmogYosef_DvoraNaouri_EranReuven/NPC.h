#pragma once
#include "Character.h"
#include "Screen.h"

using std::string;
using std::unique_ptr;
using sf::View;

class NPC : public Character // Inherit from character
{
public:
	NPC(const string & name); //constructor
	~NPC(); //destructor

	// Inherited via Character Coledrs handlers
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Door & door) override;

	// Setter
	void setChat(const string & chat) { m_chat = chat; } //chat setting

	virtual void startChat(unique_ptr<Screen> & screen, const View & view) const; //start chat setting function

private:
	string m_chat; //a string member for text for the chat when talk to the npc
};

