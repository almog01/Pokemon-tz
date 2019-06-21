#include "LoadCommand.h"
#include <sstream>
#include "Factory.h"



//constructor will init the reference members (player and start menu screen)
LoadCommand::LoadCommand(StartMenu& startm, Player& player)
	:m_startm(startm), m_player(player)
{
}


LoadCommand::~LoadCommand()
{
}

void LoadCommand::execute()
{
	ifstream loadFile("database/save_file.txt"); //open the save file
	if (!loadFile.is_open()) //if there is no such file, do nothing.
		return;

	istringstream stream; //for line stream
	string line; //to get line
	getline(loadFile, line); //get line from the file into line
	m_player.setMap(Factory::map(line)); //set the saved map

	getline(loadFile, line);
	stream.str(line); 
	sf::Vector2f playerPos; //will hold player position
	stream >> playerPos.x >> playerPos.y;
	m_player.setPosition(playerPos);

	int maxHp, hp, level, xp; //will hold the current pokemons members integers
	string pokemonName; 
	//this loop will get over all the pokemons and load the details above for each
	while (getline(loadFile, line))
	{
		stream.clear();
		stream.str(line);
		stream >> pokemonName;
		//inside loop to run over the pokemons, using iterators
		auto pokemons = m_player.cbegin();
		for (auto pokemons = m_player.cbegin(); pokemons != m_player.cend(); ++pokemons)
		{
			if ((*pokemons)->getName() == pokemonName)
			{
				stream >> maxHp >> hp >> level >> xp;
				(*pokemons)->setLevel(level).setMaxHp(maxHp).setHp(hp).setXp(xp);
			}
		}
	}
	loadFile.close();  //close the save file
	m_startm.deactivate(); //close the start menu screen and play the game
}
