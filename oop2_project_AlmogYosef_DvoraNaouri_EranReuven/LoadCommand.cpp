#include "LoadCommand.h"
#include <sstream>
#include "Factory.h"




LoadCommand::LoadCommand(StartMenu& startm, Player& player)
	:m_startm(startm), m_player(player)
{
}


LoadCommand::~LoadCommand()
{
}

void LoadCommand::execute()
{
	ifstream loadFile("database/save_file.txt");
	if (!loadFile.is_open())
		return;

	m_startm.deactivate();
	istringstream str;
	string line;
	getline(loadFile, line);
	m_player.setMap(Factory::map(line));
	sf::Vector2f playerPos;
	loadFile >> playerPos.x;
	loadFile >> playerPos.y;
	
	m_player.setPosition(playerPos);

	int maxHp, Hp, Level, Xp;
	string pokemonName;
	while (getline(loadFile, line))
	{
		str.str(line);
		str >> pokemonName;
		auto pokemons = m_player.cbegin();
		for (auto pokemons = m_player.cbegin(); pokemons != m_player.cend(); ++pokemons)
		{
			if ((*pokemons)->getName() == pokemonName)
			{
				str >> maxHp >> Hp >> Level >> Xp;
				(*pokemons)->setMaxHp(maxHp);
				(*pokemons)->setHp(Hp);
				(*pokemons)->setLevel(Level);
				(*pokemons)->setXp(Xp);
			}

		}
	}
	loadFile.close();
}
