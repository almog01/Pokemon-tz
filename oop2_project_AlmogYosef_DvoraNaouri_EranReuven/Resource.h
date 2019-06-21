#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

using sf::Texture;
using sf::Music;
using sf::Image;
using sf::Font;
using std::unordered_map;
using std::string;
using std::shared_ptr;

class Resource
{
public:
	// Singleton Resource
	static Resource& instance();
	~Resource();
	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;

	static const Texture & texture(const string & key);
	static const Image & image(const string & key);
	static const shared_ptr<Music> music(const string & key);
	static Font font;

private:
	Resource();

	// Loads a texture. Prints error message if the loading failed
	void loadTexture(const string & key, const string & path);

	// Loads a music. Prints error message if the loading failed
	void loadMusic(const string & key, const string & path);

	// Loads an image. Prints error message if the loading failed
	void loadImage(const string & key, const string & path);

	// Loads a font. Prints error message if the loading failed
	void loadFont(Font & font, const string & path);

	static unordered_map<string, Texture> m_textures;	// map of textures
	static unordered_map<string, Image> m_images;		// map of images
	static unordered_map<string, shared_ptr<Music>> m_musics;		// map of musics
};

