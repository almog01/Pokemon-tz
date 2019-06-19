#pragma once
#include "Command.h"
#include "Screen.h"
#include "Pokemon.h"
#include "Ability.h"

using sf::View;
using std::unique_ptr;
using std::shared_ptr;

class FightCommand : public Command
{
public:
	FightCommand(View & view, unique_ptr<Screen> & screen, shared_ptr<Pokemon> & player, Ability*& usedAbility);
	~FightCommand();

	// Inherited via Command
	virtual void execute() override;

private:
	View & m_view;
	unique_ptr<Screen> & m_screen;
	shared_ptr<Pokemon> & m_pokemon;
	Ability*& m_usedAbility;
};

