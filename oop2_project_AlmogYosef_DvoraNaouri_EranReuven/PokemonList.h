#pragma once
#include "Screen.h"
#include "Trainer.h"

using sf::View;
using sf::Sprite;
using sf::Text;
using std::vector;
using std::shared_ptr;

class PokemonList :	public Screen
{
public:
	PokemonList(Trainer & trainer, bool inBattle = false);
	~PokemonList();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;

	void addPokemonTile(const shared_ptr<Pokemon> & p, int index);

private:
	void updateSelection();
	void select();

	View m_view;
	bool m_inBattle;
	vector<Sprite> m_frames;
	vector<Sprite> m_sprites;
	vector<Text> m_texts;
	int m_selected;
	unique_ptr<Screen> m_menu = nullptr;
};

