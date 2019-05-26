#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

using sf::Texture;
using sf::Image;
using std::unordered_map;
using std::string;

class Resource
{
public:
	Resource();
	~Resource();

	static const Texture & texture(const string & key);
	static const Image & image(const string & key);

private:
	// Loads a texture. Prints error message if the loading failed
	void loadTexture(const string & key, const string & path);

	// Loads an image. Prints error message if the loading failed
	void loadImage(const string & key, const string & path);

	static unordered_map<string, Texture> m_textures;	// map of all textures
	static unordered_map<string, Image> m_images;		// map of all images
};

