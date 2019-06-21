#pragma once
#include "Screen.h"
#include "Trainer.h"

using sf::View;
using sf::Sprite;
using sf::Text;
using std::vector;
using std::shared_ptr;

class PokemonList :	public Screen // inherit from Screen
{
public:
	PokemonList(Trainer & trainer, int & nextPokemon, bool inBattle = false); //constructor
	~PokemonList(); //destructor

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override; ////draw function, override Screen virtual func
	virtual void keyReleasedHandler(const Event & event) override; //KeyReleasedHandler function, override Screen virtual func

	void addPokemonTile(const shared_ptr<Pokemon> & p, int index); //adding pokemon to the list function

private:
	void updateSelection(); //update selection private function (when the pokemon list is open)
	void select(); //select private function (when the pokemon list is open)

	View m_view; //view member to set the right view for that screen
	bool m_inBattle; //in battle boolian.
	vector<Sprite> m_frames; //m_frames vector for frame the selection
	vector<Sprite> m_sprites; //sprites vector for the pokemon presents
	vector<Text> m_texts; //m_texts vector to hold the texts
	int m_selected; //will hold the selected pokemon index
	unique_ptr<Screen> m_menu = nullptr; //subscreen for the menu
	int & m_nextPokemon; //next pokemon index reference
};

