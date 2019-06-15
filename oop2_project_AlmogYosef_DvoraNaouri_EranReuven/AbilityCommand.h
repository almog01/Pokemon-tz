#pragma once
#include "Command.h"
#include "Ability.h"
#include "Pokemon.h"
#include "Menu.h"

using std::shared_ptr;

class AbilityCommand : public Command
{
public:
	AbilityCommand(Menu* menu, Ability* ability, Ability*& usedAbility);
	~AbilityCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	Menu* m_menu;
	Ability* m_ability;
	Ability*& m_usedAbility;
};

