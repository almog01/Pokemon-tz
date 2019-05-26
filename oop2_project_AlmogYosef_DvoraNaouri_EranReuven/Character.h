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

	void setMapData(const vector<vector<unsigned short>> & mapData) { m_mapData = mapData; }

protected:
	void move();

	void stop();

	bool checkCollision() const;

	int getDirectionIndex(Direction dir);

	void startMove(Direction dir);


	Sprite m_sprite;		// sprite of the character
	Vector2f m_lastPos;		// last position
	Vector2f m_direction;	// current character direction
	//Direction m_direction;	// current character direction
	//int m_moveState;		// moving sprite select
	//int m_counter;			// sprite counter
	//float m_moveCounter;	// move sequence counter
	//bool m_moving;			// movement flag
	//bool m_turning;			// turning flag
	float m_moveSpeed;		// move speed
	vector<vector<unsigned short>> m_mapData;
	static const int sizeX = 16;	// x size of a texture
	static const int sizeY = 19;	// y size of a texture
};

