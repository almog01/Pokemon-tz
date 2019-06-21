#include "InstructionScreen.h"



InstructionScreen::InstructionScreen() //constructor
{
	m_view.setSize({ 2944, 1949 }); //set the view size

	//load the instructions texture
	m_screen.setTexture(Resource::texture("mainMenu_instructions"), true);
	m_screen.setPosition({ -970, -470 }); //screen position setting
}


InstructionScreen::~InstructionScreen() //destructor
{
}

void InstructionScreen::draw(RenderWindow & window)
{
	window.setView(m_view); //draw the new view setting
	window.draw(m_screen); //draw the screen
}

void InstructionScreen::keyReleasedHandler(const Event & event) 
{
	deactivate(); //any key will close the instructions screen
}
