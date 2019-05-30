#include "Resource.h"
#include <Windows.h>


unordered_map<string, Texture> Resource::m_textures{};
unordered_map<string, Image> Resource::m_images {};

Resource::Resource()
{
	loadTexture("player", "res/img/characters/player.png");
	loadTexture("vermillion", "res/img/maps/vermillion_bottom.png");
	loadTexture("cw", "res/img/characters/cw.png");
	loadImage("vermillion_data", "res/img/maps/vermillion_data.png");
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
