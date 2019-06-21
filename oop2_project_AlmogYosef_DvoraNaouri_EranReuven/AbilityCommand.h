#pragma once
#include "Command.h"
#include "Ability.h"
#include "Pokemon.h"
#include "Menu.h"

using std::shared_ptr;

class AbilityCommand : public Command // inherit from Command
{
public:
	AbilityCommand(Menu* menu, Ability* ability, Ability*& usedAbility); //constructor
	~AbilityCommand(); //destructor

	// Inherited via Command
	virtual void execute() override; //execute ovrride function to execute command

private:
	Menu* m_menu; //menu pointer to close it after command
	Ability* m_ability; //ability pointer to execute ability
	Ability*& m_usedAbility; //will hold the executed ability
};

