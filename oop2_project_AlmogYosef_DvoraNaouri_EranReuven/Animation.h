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
	Animation(Collider & collider, const Texture & texture, Vector2u imageCount, float speed);
	~Animation();

	void addAnimation(const string & name, unsigned row);

	void play(const string & name);

private:
	Collider & m_collider;
	unordered_map<string, unsigned> m_animations;
	Vector2u m_imageCount;
	Vector2u m_currImage;
	float m_speed;
	IntRect uvRect;
	float m_totalTime;
	float m_switchTime;
	bool m_forward;
};

