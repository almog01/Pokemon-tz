#pragma once
#include "Collider.h"

class Map;

using sf::Sprite;
using sf::Vector2f;
using std::vector;

class Character : public Collider
{
public:
	Character();
	virtual ~Character();

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;
	virtual void setPosition(const Vector2f & pos) { m_sprite.setPosition(pos); }
	virtual FloatRect getGlobalBounds() const override;

	virtual Vector2f getPosition() const { return m_sprite.getPosition(); }

	virtual void setMap(const Map * map);

	// Inherited via GameObject
	virtual void setTextureRect(const IntRect & rect) override;

protected:
	// Movement
	void move(bool & inGrass);
	void stop();

	bool checkMapCollision(bool & inGrass) const;

	Sprite m_sprite;		// sprite of the character
	float m_moveSpeed;		// move speed
	Vector2f m_direction;	// direction of movement
	const vector<vector<unsigned short>> * m_mapData;	// collision data of the map
	const float sizeX = 16;	// x size of the texture
	const float sizeY = 19;	// y size of the texture
};

