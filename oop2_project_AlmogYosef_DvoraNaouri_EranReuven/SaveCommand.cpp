#include "SaveCommand.h"
#include "Chat.h"
#include <sstream>

using std::make_unique;

//constructor will init the player, screen and window references
SaveCommand::SaveCommand(Player & player, unique_ptr<Screen> & screen, RenderWindow & window)
	: m_player(player), m_screen(screen), m_window(window)
{
}

SaveCommand::~SaveCommand() //destructor
{
}

void SaveCommand::execute()
{
	stringstream str; //for file stream
	ofstream saveFile ("database/save_file.txt"); //open/create save file

	saveFile << m_player.getMap(); //output to the file the map name
	saveFile << '\n'; //new line

	sf::Vector2f playerPos = m_player.getPosition(); //hold player position
	str << playerPos.x << " " << playerPos.y << '\n'; //output player position to the stream
	saveFile << str.str(); //stream it into the file

	/*run with iterators over the player's pokemons vector and get the details. will
	output to the file each pokemon details whithin a line and get a new line between
	pokemons*/
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
	saveFile.close(); //close the file

	//will make a chat screen to tell the user that the game has been saved.
	m_screen = make_unique<Chat>(Resource::texture("chat_window"), m_window.getView(), "Game saved!");
}
