#include "PokemonList.h"
#include "Menu.h"
#include "ShiftCommand.h"
#include "ExitCommand.h"

using sf::IntRect;
using sf::Keyboard;
using sf::IntRect;
using std::to_string;
using std::make_unique;

const unsigned TEXT_SIZE = 14U;

PokemonList::PokemonList(Trainer & trainer, int & nextPokemon, bool inBattle)
	: m_inBattle(inBattle), m_selected(0), m_nextPokemon(nextPokemon)
{
	m_screen.setTexture(Resource::texture("pokemon_list_bg"));
	m_view = View(m_screen.getGlobalBounds());

	int index = 0;
	for (auto pokemon = trainer.cbegin(); pokemon != trainer.cend(); ++pokemon, ++index)
		addPokemonTile(*pokemon, index);
	updateSelection();
}


PokemonList::~PokemonList()
{
}

void PokemonList::keyReleasedHandler(const Event & event)
{
	if (m_menu)
		m_menu->keyReleasedHandler(event);
	else
	{
		switch (event.key.code)
		{
		case Keyboard::X:	// x pressed
			m_active = false;
			break;
		case Keyboard::Z:	// x pressed
			select();
			break;
		case Keyboard::Left:
			m_selected = 0;
			updateSelection();
			break;
		case Keyboard::Right:
			m_selected = (m_selected == 0) ? 1 : m_selected;
			updateSelection();
			break;
		case Keyboard::Up:
			m_selected = (m_selected - 1) >= 0 ? m_selected - 1 : m_selected - 1 + int(m_frames.size());
			updateSelection();
			break;
		case Keyboard::Down:
			m_selected = (m_selected + 1) % m_frames.size();
			updateSelection();
			break;
		}
	}
}

void PokemonList::addPokemonTile(const shared_ptr<Pokemon> & p, int index)
{
	if (index == 0)
	{
		Sprite frame(Resource::texture("pokemon_list_first"), IntRect(0, 55, 84, 57));
		frame.setPosition(Vector2f(2.f, 20.f));
		m_frames.emplace_back(frame);
		Sprite icon(p->getIcon());
		icon.setPosition(frame.getPosition() + Vector2f(6.f, 7.f));
		m_sprites.emplace_back(icon);
		Sprite hpbar(p->getHpBar());
		hpbar.setPosition(frame.getPosition() + Vector2f(30.f, 39.f));
		m_sprites.emplace_back(hpbar);
		Text name(p->getName(), Resource::font, TEXT_SIZE);
		name.setFillColor(sf::Color::White);
		name.setPosition(frame.getPosition() + Vector2f(32.f, 10.f));
		m_texts.emplace_back(name);
		Text level("Lv" + to_string(p->getLevel()), Resource::font, TEXT_SIZE);
		level.setFillColor(sf::Color::White);
		level.setPosition(name.getPosition() + Vector2f(7.f, 11.f));
		m_texts.emplace_back(level);
		Text hp(to_string(p->getHp()) + "/" + to_string(p->getMaxHp()), Resource::font, TEXT_SIZE);
		hp.setFillColor(sf::Color::White);
		hp.setPosition(frame.getPosition() + Vector2f(40.f, 39.f));
		m_texts.emplace_back(hp);
	}
	else
	{
		Sprite frame(Resource::texture("pokemon_list_next"), IntRect(0, 0, 150, 22));
		frame.setPosition(Vector2f(88.f, 10.f + 24.f * (index - 1)));
		m_frames.emplace_back(frame);
		Sprite icon(p->getIcon());
		icon.setPosition(frame.getPosition() + Vector2f(5.f, 1.f));
		m_sprites.emplace_back(icon);
		Sprite hpbar(p->getHpBar());
		hpbar.setPosition(frame.getPosition() + Vector2f(96.f, 8.f));
		m_sprites.emplace_back(hpbar);
		Text name(p->getName(), Resource::font, TEXT_SIZE);
		name.setFillColor(sf::Color::White);
		name.setPosition(frame.getPosition() + Vector2f(32.f, -5.f));
		m_texts.emplace_back(name);
		Text level("Lv" + to_string(p->getLevel()), Resource::font, TEXT_SIZE);
		level.setFillColor(sf::Color::White);
		level.setPosition(name.getPosition() + Vector2f(7.f, 11.f));
		m_texts.emplace_back(level);
		Text hp(to_string(p->getHp()) + "/" + to_string(p->getMaxHp()), Resource::font, TEXT_SIZE);
		hp.setFillColor(sf::Color::White);
		hp.setPosition(hpbar.getPosition() + Vector2f(12.f, -1.f));
		m_texts.emplace_back(hp);
	}
}

void PokemonList::updateSelection()
{
	static IntRect firstSelected = IntRect(0, 55, 84, 55);
	static IntRect firstUnSelected = IntRect(0, 0, 84, 55);
	static IntRect nextSelected = IntRect(0, 22, 150, 24);
	static IntRect nextUnSelected = IntRect(0, 0, 150, 22);
	static int lastSelection = m_selected;

	m_frames[lastSelection].setTextureRect((lastSelection == 0) ? firstUnSelected : nextUnSelected);
	m_frames[m_selected].setTextureRect((m_selected == 0) ? firstSelected : nextSelected);
	lastSelection = m_selected;
}

void PokemonList::select()
{
	if (m_inBattle)
	{
		auto menu = make_unique <Menu>(Resource::texture("pokemon_list_menu"), Vector2f(1.f, 2.f));
		menu->addCommand("Shift", make_unique<ShiftCommand>(m_selected, m_nextPokemon));
		menu->addCommand("Cancel", make_unique<ExitCommand>(menu.get()));
		menu->setOrigin(BOTTOM_RIGHT);
		menu->setPosition(Vector2f(m_view.getSize().x, m_view.getSize().y));
		m_menu = std::move(menu);
	}
}

void PokemonList::draw(RenderWindow & window)
{
	window.draw(m_screen);
	for (auto& frame : m_frames)
		window.draw(frame);
	for (auto& sprite : m_sprites)
		window.draw(sprite);
	for (auto& text : m_texts)
		window.draw(text);
	if (m_menu)
	{
		if (!m_menu->isActive())
			m_menu.reset();
		else
			m_menu->draw(window);
	}
	window.setView(m_view);
}
