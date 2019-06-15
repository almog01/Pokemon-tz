#include "AbilityCommand.h"


AbilityCommand::AbilityCommand(Menu* menu, Ability* ability, Ability*& usedAbility)
	: m_menu(menu), m_ability(ability), m_usedAbility(usedAbility)
{
}


AbilityCommand::~AbilityCommand()
{
}

void AbilityCommand::execute()
{
	m_usedAbility = m_ability;
	m_menu->deactivate();
}
