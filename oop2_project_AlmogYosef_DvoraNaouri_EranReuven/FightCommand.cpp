#include "FightCommand.h"
#include "Menu.h"
#include "AbilityCommand.h"

using std::make_shared;

const int NUM_OF_ABILITIES = 4;

FightCommand::FightCommand(View & view, unique_ptr<Screen> & screen, shared_ptr<Pokemon> & player, Ability*& usedAbility)
	: m_view(view), m_screen(screen), m_pokemon(player), m_usedAbility(usedAbility)
{
}


FightCommand::~FightCommand()
{
}

void FightCommand::execute()
{
	auto menu = std::make_unique<Menu>(Resource::texture("battle_menu_abilities"), Vector2f(2.f, 2.f));
	menu->setTextSize(16U);
	menu->setTextMarginX(38.f);
	for (int i = 0; i < NUM_OF_ABILITIES; ++i)
	{
		auto ability = m_pokemon->getAbility(i);
		if (ability)
			menu->addCommand(ability->getName(), std::make_unique<AbilityCommand>(menu.get(), ability, m_usedAbility));
		else
			menu->addCommand("-", nullptr);
	}
	menu->setOrigin(BOTTOM_LEFT);
	menu->setPosition(Vector2f(2, m_view.getCenter().y + m_view.getSize().y / 2.f));
	m_screen = std::move(menu);
}
