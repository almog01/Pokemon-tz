#include "Resource.h"
#include <Windows.h>


unordered_map<string, Texture> Resource::m_textures{};
unordered_map<string, Image> Resource::m_images{};
Font Resource::font;

Resource::Resource()
{
	loadFont(font, "resource/font/pokemon_fire_red.ttf");

	loadTexture("player", "resource/img/characters/player.png");
	loadTexture("professor_oak", "resource/img/characters/professor_oak.png");

	loadTexture("pallet", "resource/img/maps/pallet/pallet.png");
	loadImage("pallet_data", "resource/img/maps/pallet/pallet_data.png");

	loadTexture("oaks_lab", "resource/img/maps/oaks_lab/oaks_lab.png");
	loadImage("oaks_lab_data", "resource/img/maps/oaks_lab/oaks_lab_data.png");

	loadTexture("vermillion", "resource/img/maps/vermillion/vermillion.png");
	loadImage("vermillion_data", "resource/img/maps/vermillion/vermillion_data.png");

	loadTexture("chat_window", "resource/img/interface/chat_window.png");
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
