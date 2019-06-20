#include "SaveCommand.h"
#include "Chat.h"
#include <sstream>

using std::make_unique;

SaveCommand::SaveCommand(Player & player, unique_ptr<Screen> & screen, RenderWindow & window)
	: m_player(player), m_screen(screen), m_window(window)
{
}

SaveCommand::~SaveCommand()
{
}

void SaveCommand::execute()
{
	stringstream str;
	ofstream saveFile ("database/save_file.txt");

	saveFile << m_player.getMap();
	saveFile << '\n';

	sf::Vector2f playerPos = m_player.getPosition();
	str << playerPos.x << " " << playerPos.y << '\n';
	saveFile << str.str();

	for (auto pokemons = m_player.cbegin(); pokemons != m_player.cend(); ++pokemons)
	{
		saveFile << (*pokemons)->getName();
		saveFile << " ";
		saveFile << (*pokemons)->getMaxHp();
		saveFile << " ";
		saveFile << (*pokemons)->getHp();
		saveFile << " ";
		saveFile << (*pokemons)->getLevel();
		saveFile << " ";
		saveFile << (*pokemons)->getXp();
		saveFile << '\n';
	}
	saveFile.close();
	m_screen = make_unique<Chat>(Resource::texture("chat_window"), m_window.getView(), "Game saved!");
}
