#pragma once
#include "Screen.h"
#include "Command.h"
#include "Utils.h"

using std::vector;
using std::pair;
using std::unique_ptr;
using sf::Text;
using sf::Vector2f;

class Menu : public Screen
{
public:
	Menu(const Texture & texture, const Vector2f & size, bool exitable = true, const Texture & arrow = Resource::texture("arrow"));
	~Menu();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;

	void addCommand(const string & name, unique_ptr<Command> c);

	// Setters
	void setOrigin(SPOT spot) { Utils::setOrigin(m_screen, spot); }
	void setPosition(const Vector2f & pos) { m_screen.setPosition(pos); }
	void setTextSize(unsigned size) { m_textSize = size; }
	void setTextMarginX(float margin) { m_textMarginX = margin; }
	void setTextMarginY(float margin) { m_textMarginY = margin; }

	void select();

private:
	typedef pair<string, unique_ptr<Command>> option;
	vector<option> m_commands;
	Vector2f m_size;
	bool m_exitable;			// flag if can exit menu with x button
	vector<Text> m_texts;
	unsigned m_textSize;
	float m_textMarginX;
	float m_textMarginY;
	Sprite m_arrow;
	Vector2f m_curSelection;
	Vector2f m_textPos;
};

