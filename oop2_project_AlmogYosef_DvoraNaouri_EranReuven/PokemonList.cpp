#include "PokemonList.h"
#include "Menu.h"
#include "ShiftCommand.h"
#include "ExitCommand.h"

using sf::IntRect;
using sf::Keyboard;
using sf::IntRect;
using std::to_string;
using std::make_unique;

const unsigned TEXT_SIZE = 14U; //constant unsigned text size

//constructor will init trainer, next pokemon and selected index.
//also, the boolian to figure if we are in a battle or not.
PokemonList::PokemonList(Trainer & trainer, int & nextPokemon, bool inBattle)
	: m_inBattle(inBattle), m_selected(0), m_nextPokemon(nextPokemon)
{
	m_screen.setTexture(Resource::texture("pokemon_list_bg")); //screen background set
	m_view = View(m_screen.getGlobalBounds()); //setting the view

	int index = 0; //start index is 0
	//run over pokemons vector via iterator
	for (auto pokemon = trainer.cbegin(); pokemon != trainer.cend(); ++pokemon, ++index)
		addPokemonTile(*pokemon, index); //adding the pokemon into the list
	updateSelection(); //update the selection func
}


PokemonList::~PokemonList() //destructor
{
}

void PokemonList::keyReleasedHandler(const Event & event)
{
	if (m_menu) //if the menu is open, use hes key handlers.
		m_menu->keyReleasedHandler(event);
	else //in any default case, keys handling will follow:
	{
		switch (event.key.code)
		{
		case Keyboard::X:	// x pressed
			m_active = false;
			break;
		case Keyboard::Z:	// z pressed
			select();
			break;
		case Keyboard::Left: //left button pressed
			m_selected = 0;
			updateSelection();
			break;
		case Keyboard::Right: //right button pressed
			m_selected = (m_selected == 0) ? 1 : m_selected;
			updateSelection();
			break;
		case Keyboard::Up: //up button pressed
			m_selected = (m_selected - 1) >= 0 ? m_selected - 1 : m_selected - 1 + int(m_frames.size());
			updateSelection();
			break;
		case Keyboard::Down: //down button pressed
			m_selected = (m_selected + 1) % m_frames.size();
			updateSelection();
			break;
		}
	}
}
//function to add pokemons into the list
void PokemonList::addPokemonTile(const shared_ptr<Pokemon> & p, int index) 
{
	if (index == 0) //first pokemon will present in a different way than the others,
	{				//so if it the first pokemon enter that condition
		/*Frame settings for the first pokemon in the list*/
		Sprite frame(Resource::texture("pokemon_list_first"), IntRect(0, 55, 84, 57)); 
		frame.setPosition(Vector2f(2.f, 20.f)); 
		m_frames.emplace_back(frame);

		/*icon setting of the pokemon*/
		Sprite icon(p->getIcon());
		icon.setPosition(frame.getPosition() + Vector2f(6.f, 7.f));
		m_sprites.emplace_back(icon);

		/*hp bar setting of the pokemon*/
		Sprite hpbar(p->getHpBar());
		hpbar.setPosition(frame.getPosition() + Vector2f(30.f, 39.f));
		m_sprites.emplace_back(hpbar);

		/*pokemon name setting*/
		Text name(p->getName(), Resource::font, TEXT_SIZE);
		name.setFillColor(sf::Color::White);
		name.setPosition(frame.getPosition() + Vector2f(32.f, 10.f));
		m_texts.emplace_back(name);

		/*pokemon level setting*/
		Text level("Lv" + to_string(p->getLevel()), Resource::font, TEXT_SIZE);
		level.setFillColor(sf::Color::White);
		level.setPosition(name.getPosition() + Vector2f(7.f, 11.f));
		m_texts.emplace_back(level);
		
		/*pokemon hp (text) setting*/
		Text hp(to_string(p->getHp()) + "/" + to_string(p->getMaxHp()), Resource::font, TEXT_SIZE);
		hp.setFillColor(sf::Color::White);
		hp.setPosition(frame.getPosition() + Vector2f(40.f, 39.f));
		m_texts.emplace_back(hp);
	}
	else //if its not the first pokemon, means its the rest of them in the right list
	{
		/*Frame settings for the rest pokemons in the list*/
		Sprite frame(Resource::texture("pokemon_list_next"), IntRect(0, 0, 150, 22));
		frame.setPosition(Vector2f(88.f, 10.f + 24.f * (index - 1)));
		m_frames.emplace_back(frame);
		
		/*icon setting of the pokemon*/
		Sprite icon(p->getIcon());
		icon.setPosition(frame.getPosition() + Vector2f(5.f, 1.f));
		m_sprites.emplace_back(icon);

		/*hp bar setting of the pokemon*/
		Sprite hpbar(p->getHpBar());
		hpbar.setPosition(frame.getPosition() + Vector2f(96.f, 8.f));
		m_sprites.emplace_back(hpbar);

		/*pokemon name setting*/
		Text name(p->getName(), Resource::font, TEXT_SIZE);
		name.setFillColor(sf::Color::White);
		name.setPosition(frame.getPosition() + Vector2f(32.f, -5.f));
		m_texts.emplace_back(name);

		/*pokemon level setting*/
		Text level("Lv" + to_string(p->getLevel()), Resource::font, TEXT_SIZE);
		level.setFillColor(sf::Color::White);
		level.setPosition(name.getPosition() + Vector2f(7.f, 11.f));
		m_texts.emplace_back(level);

		/*pokemon hp (text) setting*/
		Text hp(to_string(p->getHp()) + "/" + to_string(p->getMaxHp()), Resource::font, TEXT_SIZE);
		hp.setFillColor(sf::Color::White);
		hp.setPosition(hpbar.getPosition() + Vector2f(12.f, -1.f));
		m_texts.emplace_back(hp);
	}
}

void PokemonList::updateSelection() //updating the selection frames and
{									//points over the lists 
	static IntRect firstSelected = IntRect(0, 55, 84, 55); //first place selected
	static IntRect firstUnSelected = IntRect(0, 0, 84, 55); //first place unselected
	static IntRect nextSelected = IntRect(0, 22, 150, 24); //next pokemon selected
	static IntRect nextUnSelected = IntRect(0, 0, 150, 22); //next pokemon unselected
	static int lastSelection = m_selected; //last selected update

	//frames updates//
	m_frames[lastSelection].setTextureRect((lastSelection == 0) ? firstUnSelected : nextUnSelected);
	m_frames[m_selected].setTextureRect((m_selected == 0) ? firstSelected : nextSelected);
	lastSelection = m_selected;
}

void PokemonList::select() //select function of the list
{
	if (m_inBattle) //if we are in battle, enter this condition
	{
		auto menu = make_unique <Menu>(Resource::texture("pokemon_list_menu"), Vector2f(1.f, 2.f));
		menu->addCommand("Shift", make_unique<ShiftCommand>(m_selected, m_nextPokemon)); //shift pokemons command
		menu->addCommand("Cancel", make_unique<ExitCommand>(menu.get())); //Cancel shifting command
		
		//menu settings//
		menu->setOrigin(BOTTOM_RIGHT);
		menu->setPosition(Vector2f(m_view.getSize().x, m_view.getSize().y));
		m_menu = std::move(menu);
	}
}

void PokemonList::draw(RenderWindow & window) //draw function
{
	window.draw(m_screen); //draw the screen
	for (auto& frame : m_frames) //draw the frames in a loop using iterator
		window.draw(frame);
	for (auto& sprite : m_sprites) //draw the sprites in a loop using iterator
		window.draw(sprite);
	for (auto& text : m_texts) //draw the texts in a loop using iterator
		window.draw(text);
	if (m_menu) //if the menu is exsist
	{
		if (!m_menu->isActive()) //check if its still active
			m_menu.reset(); //delete it if not
		else
			m_menu->draw(window); //else, draw it
	}
	window.setView(m_view); //setting the window view
}
