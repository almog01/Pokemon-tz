#pragma once
#include "Screen.h"
#include "Command.h"
#include "Utils.h"

using std::vector;
using std::pair;
using std::unique_ptr;
using sf::Text;
using sf::Vector2f;

class Menu : public Screen // Inherit from screen
{
public:
	Menu(const Texture & texture, const Vector2f & size, bool exitable = true, const Texture & arrow = Resource::texture("arrow")); //constructor
	~Menu(); //destructor

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;

	void addCommand(const string & name, unique_ptr<Command> c); //add command function to the menu

	// Set functions for the menu screen, and for the texts over it
	void setOrigin(SPOT spot) { Utils::setOrigin(m_screen, spot); }
	void setPosition(const Vector2f & pos);
	void setTextSize(unsigned size) { m_textSize = size; }
	void setTextMarginX(float margin) { m_textMarginX = margin; }
	void setTextMarginY(float margin) { m_textMarginY = margin; }

	void select(); //select function

protected: //will use in inherits classes
	typedef pair<string, unique_ptr<Command>> option; //define pair option of command type
	vector<option> m_commands; //vector of commands
	Vector2f m_size; //hold the size of the menu
	bool m_exitable; // flag if can exit menu with x button

	/*texts members for settings and contain them*/
	vector<Text> m_texts;
	unsigned m_textSize;
	float m_textMarginX;
	float m_textMarginY;

	/*members to visual the selections (by arrow sprite) and selection position*/
	Sprite m_arrow;
	Vector2f m_curSelection;
	Vector2f m_textPos;
};

