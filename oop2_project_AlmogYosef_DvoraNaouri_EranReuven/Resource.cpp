#include "Resource.h"
#include <Windows.h>


unordered_map<string, Texture> Resource::m_textures;
unordered_map<string, Image> Resource::m_images;
unordered_map<string, shared_ptr<Music>> Resource::m_musics;
Font Resource::font;

Resource::Resource()
{
	// game font
	loadFont(font, "resource/font/pokemon_fire_red.ttf");
	
	// music
	loadMusic("startmenu", "resource/music/startmenu.ogg");
	loadMusic("background", "resource/music/background.ogg");
	loadMusic("battle", "resource/music/battle.ogg");

	// start menu
	loadTexture("start_menu_bg", "resource/img/startmenu/pokemon-tz.png");
	loadTexture("main_menu", "resource/img/startmenu/MainMenu.png");
	loadTexture("mainMenu_arrow", "resource/img/startmenu/mainMarrow.png");
	loadTexture("mainMenu_instructions", "resource/img/startmenu/Instructions.png");

	// characters
	loadTexture("player", "resource/img/characters/player.png");
	loadTexture("mom", "resource/img/characters/mom.png");
	loadTexture("professor_oak", "resource/img/characters/professor_oak.png");
	loadTexture("trainer1", "resource/img/characters/trainer1.png");
	loadTexture("trainer2", "resource/img/characters/trainer2.png");
	loadTexture("trainer3", "resource/img/characters/trainer3.png");
	loadTexture("trainer4", "resource/img/characters/trainer4.png");
	loadTexture("trainer5", "resource/img/characters/trainer5.png");
	loadTexture("trainer6", "resource/img/characters/trainer6.png");
	loadTexture("nurse", "resource/img/characters/nurse.png");
	loadTexture("shop_npc", "resource/img/characters/shop_npc.png");
	loadTexture("npc1", "resource/img/characters/npc1.png");
	loadTexture("npc2", "resource/img/characters/npc2.png");
	loadTexture("npc3", "resource/img/characters/npc3.png");
	loadTexture("npc4", "resource/img/characters/npc4.png");
	loadTexture("npc5", "resource/img/characters/npc5.png");
	loadTexture("npc6", "resource/img/characters/npc6.png");
	loadTexture("npc7", "resource/img/characters/npc7.png");
	loadTexture("npc8", "resource/img/characters/npc8.png");
	loadTexture("npc9", "resource/img/characters/npc9.png");

	// maps
	loadTexture("home", "resource/img/maps/home/home.png");
	loadImage("home_data", "resource/img/maps/home/home_data.png");
	loadTexture("pallet", "resource/img/maps/pallet/pallet.png");
	loadImage("pallet_data", "resource/img/maps/pallet/pallet_data.png");
	loadTexture("oaks_lab", "resource/img/maps/oaks_lab/oaks_lab.png");
	loadImage("oaks_lab_data", "resource/img/maps/oaks_lab/oaks_lab_data.png");
	loadTexture("route1", "resource/img/maps/route1/route1.png");
	loadImage("route1_data", "resource/img/maps/route1/route1_data.png");
	loadTexture("viridian", "resource/img/maps/viridian/viridian.png");
	loadImage("viridian_data", "resource/img/maps/viridian/viridian_data.png");
	loadTexture("pharmacy", "resource/img/maps/pharmacy/pharmacy.png");
	loadImage("pharmacy_data", "resource/img/maps/pharmacy/pharmacy_data.png");
	loadTexture("shop", "resource/img/maps/shop/shop.png");
	loadImage("shop_data", "resource/img/maps/shop/shop_data.png");
	loadTexture("house1", "resource/img/maps/house1/house1.png");
	loadImage("house1_data", "resource/img/maps/house1/house1_data.png");
	loadTexture("gym", "resource/img/maps/gym/gym.png");
	loadImage("gym_data", "resource/img/maps/gym/gym_data.png");
	loadTexture("route2", "resource/img/maps/route2/route2.png");
	loadImage("route2_data", "resource/img/maps/route2/route2_data.png");
	
	// interface
	loadTexture("chat_window", "resource/img/interface/chat_window.png");
	loadTexture("menu", "resource/img/interface/menu.png");
	loadTexture("arrow", "resource/img/interface/arrow.png");
	loadTexture("boolean_menu", "resource/img/interface/boolean_menu.png");

	// battle screen
	loadTexture("battle", "resource/img/battle/battle_sheet.png");
	loadTexture("battle_menu_frame", "resource/img/battle/battle_menu_frame.png");
	loadTexture("battle_menu_bg", "resource/img/battle/battle_menu_bg.png");
	loadTexture("battle_menu_abilities", "resource/img/battle/battle_menu_abilities.png");
	loadTexture("battle_player_statbar", "resource/img/battle/battle_player_statbar.png");
	loadTexture("battle_enemy_statbar", "resource/img/battle/battle_enemy_statbar.png");
	loadTexture("battle_hpbar", "resource/img/battle/battle_hpbar.png");
	loadTexture("battle_expbar", "resource/img/battle/battle_expbar.png");

	// pokemon list screen
	loadTexture("pokemon_list_bg", "resource/img/pokemon_list/background.png");
	loadTexture("pokemon_list_first", "resource/img/pokemon_list/first_pokemon.png");
	loadTexture("pokemon_list_next", "resource/img/pokemon_list/next_pokemon.png");
	loadTexture("pokemon_list_menu", "resource/img/pokemon_list/menu_frame.png");

	// abilities
	loadTexture("NORMAL_ability", "resource/img/abilities/normal.png");
	loadTexture("ELECTRIC_ability", "resource/img/abilities/electric.png");
	loadTexture("GROUND_ability", "resource/img/abilities/ground.png");
	loadTexture("FIRE_ability", "resource/img/abilities/fire.png");
	loadTexture("WATER_ability", "resource/img/abilities/water.png");
	loadTexture("FLYING_ability", "resource/img/abilities/flying.png");
	loadTexture("GRASS_ability", "resource/img/abilities/grass.png");
	loadTexture("PSYCHIC_ability", "resource/img/abilities/psychic.png");

	// pokemons
	loadTexture("blastoise_front", "resource/img/pokemons/blastoise/front.png");
	loadTexture("blastoise_back", "resource/img/pokemons/blastoise/back.png");
	loadTexture("blastoise_icon", "resource/img/pokemons/blastoise/icon.png");
	loadTexture("butterfree_front", "resource/img/pokemons/butterfree/front.png");
	loadTexture("butterfree_back", "resource/img/pokemons/butterfree/back.png");
	loadTexture("butterfree_icon", "resource/img/pokemons/butterfree/icon.png");
	loadTexture("caterpie_front", "resource/img/pokemons/caterpie/front.png");
	loadTexture("caterpie_back", "resource/img/pokemons/caterpie/back.png");
	loadTexture("caterpie_icon", "resource/img/pokemons/caterpie/icon.png");
	loadTexture("charizard_front", "resource/img/pokemons/charizard/front.png");
	loadTexture("charizard_back", "resource/img/pokemons/charizard/back.png");
	loadTexture("charizard_icon", "resource/img/pokemons/charizard/icon.png");
	loadTexture("dodrio_front", "resource/img/pokemons/dodrio/front.png");
	loadTexture("dodrio_back", "resource/img/pokemons/dodrio/back.png");
	loadTexture("dodrio_icon", "resource/img/pokemons/dodrio/icon.png");
	loadTexture("farfetchd_front", "resource/img/pokemons/farfetchd/front.png");
	loadTexture("farfetchd_back", "resource/img/pokemons/farfetchd/back.png");
	loadTexture("farfetchd_icon", "resource/img/pokemons/farfetchd/icon.png");
	loadTexture("magneton_front", "resource/img/pokemons/magneton/front.png");
	loadTexture("magneton_back", "resource/img/pokemons/magneton/back.png");
	loadTexture("magneton_icon", "resource/img/pokemons/magneton/icon.png");
	loadTexture("mew_front", "resource/img/pokemons/mew/front.png");
	loadTexture("mew_back", "resource/img/pokemons/mew/back.png");
	loadTexture("mew_icon", "resource/img/pokemons/mew/icon.png");
	loadTexture("mewtwo_front", "resource/img/pokemons/mewtwo/front.png");
	loadTexture("mewtwo_back", "resource/img/pokemons/mewtwo/back.png");
	loadTexture("mewtwo_icon", "resource/img/pokemons/mewtwo/icon.png");
	loadTexture("pidgeot_front", "resource/img/pokemons/pidgeot/front.png");
	loadTexture("pidgeot_back", "resource/img/pokemons/pidgeot/back.png");
	loadTexture("pidgeot_icon", "resource/img/pokemons/pidgeot/icon.png");
	loadTexture("pikachu_front", "resource/img/pokemons/pikachu/front.png");
	loadTexture("pikachu_back", "resource/img/pokemons/pikachu/back.png");
	loadTexture("pikachu_icon", "resource/img/pokemons/pikachu/icon.png");
	loadTexture("ponyta_front", "resource/img/pokemons/ponyta/front.png");
	loadTexture("ponyta_back", "resource/img/pokemons/ponyta/back.png");
	loadTexture("ponyta_icon", "resource/img/pokemons/ponyta/icon.png");
	loadTexture("venusaur_front", "resource/img/pokemons/venusaur/front.png");
	loadTexture("venusaur_back", "resource/img/pokemons/venusaur/back.png");
	loadTexture("venusaur_icon", "resource/img/pokemons/venusaur/icon.png");
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

const shared_ptr<Music> Resource::music(const string & key)
{
	return m_musics.at(key);
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

void Resource::loadMusic(const string & key, const string & path)
{
	shared_ptr<Music> music = std::make_shared<Music>();	// create new music
	if (!music->openFromFile(path))	// try load the music
	{
		MessageBoxA(NULL, "Error loading music", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
	music->setLoop(true);
	m_musics[key] = std::move(music);	// add the music to the unordered map
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
