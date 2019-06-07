#include "Resource.h"
#include <Windows.h>


unordered_map<string, Texture> Resource::m_textures{};
unordered_map<string, Image> Resource::m_images {};

Resource::Resource()
{
	loadTexture("player", "res/img/characters/player.png");
	loadTexture("professor_oak", "res/img/characters/professor_oak.png");

	loadTexture("pallet", "res/img/maps/pallet/pallet.png");
	loadImage("pallet_data", "res/img/maps/pallet/pallet_data.png");

	loadTexture("oaks_lab", "res/img/maps/oaks_lab/oaks_lab.png");
	loadImage("oaks_lab_data", "res/img/maps/oaks_lab/oaks_lab_data.png");

	loadTexture("vermillion", "res/img/maps/vermillion/vermillion.png");
	loadImage("vermillion_data", "res/img/maps/vermillion/vermillion_data.png");
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
		MessageBoxA(NULL, "Error loading texture", "Error", MB_OK | MB_ICONEXCLAMATION);	// print error message
		exit(EXIT_FAILURE);
	}
	m_images[key] = image;	// add the image to the unordered map
}
