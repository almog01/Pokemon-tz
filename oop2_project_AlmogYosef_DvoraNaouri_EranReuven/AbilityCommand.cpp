#include "AbilityCommand.h"

//constructor will init the menu, ability pointers and the usedAbility reference pointer
AbilityCommand::AbilityCommand(Menu* menu, Ability* ability, Ability*& usedAbility)
	: m_menu(menu), m_ability(ability), m_usedAbility(usedAbility)
{
}


AbilityCommand::~AbilityCommand() //destructor
{
}

void AbilityCommand::execute()
{
	m_usedAbility = m_ability; //save the used ability (on reference pointer)
	m_menu->deactivate(); //deactivate the menu that sent
}
