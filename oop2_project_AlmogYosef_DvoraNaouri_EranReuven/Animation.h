#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Collider.h"

using std::unordered_map;
using std::string;
using sf::Texture;
using sf::Vector2u;
using sf::IntRect;

class Animation
{
public:
	Animation(Collider & collider, const Texture & texture, Vector2u imageCount, float speed);	// c-tor
	~Animation();	// d-tor

	// adds an animation by his name
	void addAnimation(const string & name, unsigned row);

	// plays an animation by his name
	void play(const string & name);

private:
	unordered_map<string, unsigned> m_animations;	// unordered_map for all the animations by their names
	Collider & m_collider;	// the collider that the animation is attached to
	Vector2u m_imageCount;	// number of rows and columns in the loaded image
	Vector2u m_currImage;	// current displayed image index
	float m_speed;			// animation speed
	IntRect uvRect;			// rect to calculate the actual size of the loaded image 
	float m_totalTime;		// total time of the current played image
	float m_switchTime;		// time to pass between each image switch
	bool m_forward;			// flag if the switch between images is forward of backward
};

