#include "SaveCommand.h"
#include <sstream>


SaveCommand::SaveCommand(Player & player)
	: m_player(player)
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
}
