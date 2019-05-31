#pragma once
#include "GameObject.h"

using sf::Sprite;
using sf::Vector2f;
using std::vector;

class Character : public GameObject
{
public:
	Character();
	virtual ~Character();

	// Inherited via GameObject
	virtual void draw(RenderWindow & window) override;

	virtual void setPosition(const Vector2f & pos) { m_sprite.setPosition(pos); }
	virtual Vector2f getPosition() const { return m_sprite.getPosition(); }

	virtual void update();

	void setMapData(const vector<vector<unsigned short>> * mapData) { m_mapData = mapData; }

	// Inherited via GameObject
	virtual void setTextureRect(const IntRect & rect) override;

protected:
	void move();

	void stop();

	bool checkMapCollision() const;

	Sprite m_sprite;		// sprite of the character
	float m_moveSpeed;		// move speed
	Vector2f m_direction;	// direction of movement
	const vector<vector<unsigned short>> * m_mapData;	// collision data of the map
	static const int sizeX = 16;	// x size of a texture
	static const int sizeY = 19;	// y size of a texture
};

