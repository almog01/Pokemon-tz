#include "Resource.h"
#include <Windows.h>


unordered_map<string, Texture> Resource::m_textures;
unordered_map<string, Image> Resource::m_images;
Font Resource::font;

Resource::Resource()
{
	loadFont(font, "resource/font/pokemon_fire_red.ttf");

	loadTexture("start_menu_bg", "resource/img/startmenu/pokemon-tz.png");
	loadTexture("main_menu", "resource/img/startmenu/MainMenu.png");
	loadTexture("mainMenu_arrow", "resource/img/startmenu/mainMarrow.png");


	loadTexture("player", "resource/img/characters/player.png");
	loadTexture("professor_oak", "resource/img/characters/professor_oak.png");

	loadTexture("pallet", "resource/img/maps/pallet/pallet.png");
	loadImage("pallet_data", "resource/img/maps/pallet/pallet_data.png");

	loadTexture("oaks_lab", "resource/img/maps/oaks_lab/oaks_lab.png");
	loadImage("oaks_lab_data", "resource/img/maps/oaks_lab/oaks_lab_data.png");

	loadTexture("vermillion", "resource/img/maps/vermillion/vermillion.png");
	loadImage("vermillion_data", "resource/img/maps/vermillion/vermillion_data.png");

	loadTexture("chat_window", "resource/img/interface/chat_window.png");
	loadTexture("menu", "resource/img/interface/menu.png");
	loadTexture("arrow", "resource/img/interface/arrow.png");
	loadTexture("pokeball", "resource/img/interface/pokeball.png");

	loadTexture("battle", "resource/img/battle/battle_sheet.png");
	loadTexture("battle_menu_frame", "resource/img/battle/battle_menu_frame.png");
	loadTexture("battle_menu_bg", "resource/img/battle/battle_menu_bg.png");
	loadTexture("battle_menu_abilities", "resource/img/battle/battle_menu_abilities.png");
	loadTexture("battle_player_statbar", "resource/img/battle/battle_player_statbar.png");
	loadTexture("battle_enemy_statbar", "resource/img/battle/battle_enemy_statbar.png");
	loadTexture("battle_hpbar", "resource/img/battle/battle_hpbar.png");
	loadTexture("battle_expbar", "resource/img/battle/battle_expbar.png");

	loadTexture("pokemon_list_bg", "resource/img/pokemon_list/background.png");
	loadTexture("pokemon_list_first", "resource/img/pokemon_list/first_pokemon.png");
	loadTexture("pokemon_list_next", "resource/img/pokemon_list/next_pokemon.png");
	loadTexture("pokemon_list_menu", "resource/img/pokemon_list/menu_frame.png");

	loadTexture("pikachu_front", "resource/img/pokemons/pikachu/front.png");
	loadTexture("pikachu_back", "resource/img/pokemons/pikachu/back.png");
	loadTexture("pikachu_icon", "resource/img/pokemons/pikachu/icon.png");
	loadTexture("mew_front", "resource/img/pokemons/mew/front.png");
	loadTexture("mew_back", "resource/img/pokemons/mew/back.png");
	loadTexture("mew_icon", "resource/img/pokemons/mew/icon.png");
	loadTexture("mewtwo_front", "resource/img/pokemons/mewtwo/front.png");
	loadTexture("mewtwo_back", "resource/img/pokemons/mewtwo/back.png");
	loadTexture("mewtwo_icon", "resource/img/pokemons/mewtwo/icon.png");
}


Resource & Resource::instance()
{
	static Resource inst;
	return inst;
}

Resource::~Resource()
{
}

const Texture & Resource::texture(const string & key)
{
	return m_textures.at(key);
}

const Image & Resource::image(const string & key)
{
	return m_images.at(key);
}

void Resource::loadTexture(const string & key, const string & path)
{
	Texture texture;	// create new texture
	if (!texture.loadFromFile(path))	// try load the texture
	{
		MessageBoxA(NULL, "Error loading texture", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
	m_textures[key] = texture;	// add the texture to the unordered map
}

void Resource::loadImage(const string & key, const string & path)
{
	Image image;	// create new image
	if (!image.loadFromFile(path))	// try load the image
	{
		MessageBoxA(NULL, "Error loading image", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
	m_images[key] = image;	// add the image to the unordered map
}

void Resource::loadFont(Font & font, const string & path)
{
	if (!font.loadFromFile(path))	// try load the font
	{
		MessageBoxA(NULL, "Error loading font", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
}
