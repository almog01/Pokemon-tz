#pragma once
#include "Command.h"
#include "Screen.h"
#include "Pokemon.h"
#include "Ability.h"

using sf::View;
using std::unique_ptr;
using std::shared_ptr;

class FightCommand : public Command // inherit from Command
{
public:
	FightCommand(View & view, unique_ptr<Screen> & screen, shared_ptr<Pokemon> & player, Ability*& usedAbility); //constructor
	~FightCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command

private:
	View & m_view; //screen view reference to calculate positions
	unique_ptr<Screen> & m_screen; //screen reference
	shared_ptr<Pokemon> & m_pokemon; //pokemon reference
	Ability*& m_usedAbility; //used ability pointer reference
};

