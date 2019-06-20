#include "InstructionScreen.h"



InstructionScreen::InstructionScreen()
{
	m_view.setSize({ 2944, 1949 });
	m_screen.setTexture(Resource::texture("mainMenu_instructions"), true);
	m_screen.setPosition({ -970, -470 });
}


InstructionScreen::~InstructionScreen()
{
}

void InstructionScreen::draw(RenderWindow & window)
{
	window.setView(m_view);
	window.draw(m_screen);
}

void InstructionScreen::keyReleasedHandler(const Event & event)
{
}
