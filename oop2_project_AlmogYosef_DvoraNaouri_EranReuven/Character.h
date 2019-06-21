#pragma once
#include "Collider.h"

class Map;

using sf::Sprite;
using sf::Vector2f;
using std::vector;

class Character : public Collider
{
public:
	Character();			// c-tor
	virtual ~Character();	// d-tor

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;
	virtual void setPosition(const Vector2f & pos) { m_sprite.setPosition(pos); }
	virtual FloatRect getGlobalBounds() const override;
	virtual void setTextureRect(const IntRect & rect) override;

	// returns character's position
	virtual Vector2f getPosition() const { return m_sprite.getPosition(); }

	// sets the map that the character is within
	virtual void setMap(const Map * map);

protected:
	// moves the character, while also returns if moving in grass
	void move(bool & inGrass);
	// stops the character from moving
	void stop();

	// checks the collision of the character with the map static objects, and returns if collided with something
	bool checkMapCollision(bool & inGrass) const;

	Sprite m_sprite;		// sprite of the character
	float m_moveSpeed;		// move speed
	Vector2f m_direction;	// direction of movement
	const vector<vector<unsigned short>> * m_mapData;	// collision data of the map
	const float sizeX = 16;	// x size of the texture
	const float sizeY = 19;	// y size of the texture
};

