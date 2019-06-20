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

	istringstream stream;
	string line;
	getline(loadFile, line);
	m_player.setMap(Factory::map(line));

	getline(loadFile, line);
	stream.str(line);
	sf::Vector2f playerPos;
	stream >> playerPos.x >> playerPos.y;
	m_player.setPosition(playerPos);

	int maxHp, hp, level, xp;
	string pokemonName;
	while (getline(loadFile, line))
	{
		stream.clear();
		stream.str(line);
		stream >> pokemonName;
		auto pokemons = m_player.cbegin();
		for (auto pokemons = m_player.cbegin(); pokemons != m_player.cend(); ++pokemons)
		{
			if ((*pokemons)->getName() == pokemonName)
			{
				stream >> maxHp >> hp >> level >> xp;
				(*pokemons)->setMaxHp(maxHp).setHp(hp).setLevel(level).setXp(xp);
			}
		}
	}
	loadFile.close();
	m_startm.deactivate();
}
