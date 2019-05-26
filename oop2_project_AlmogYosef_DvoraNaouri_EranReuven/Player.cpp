#include "Player.h"

using sf::Keyboard;

Player::Player()
{
	m_sprite.setTexture(Resource::texture("player"), true);
	m_sprite.setTextureRect(sf::IntRect(16, 0, 17, 19));
}


Player::~Player()
{
}

void Player::update()
{
	/*if (m_moving)		
		Character::update();*/
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		//m_sprite.move({ 0, -m_moveSpeed });	// up = {0, -y}
		m_direction = Vector2f(0, -m_moveSpeed);
		move();
		/*m_direction = Up;
		m_moving = true;*/
		//startMove(Up);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		//m_sprite.move({ 0, m_moveSpeed });	// down = {0, y}	
		m_direction = Vector2f(0, m_moveSpeed);
		move();
		/*m_direction = Down;
		m_moving = true;*/
		//startMove(Down);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		//m_sprite.move({ -m_moveSpeed, 0 });	// left = {-x, 0}
		m_direction = Vector2f(-m_moveSpeed, 0);
		move();
		/*m_direction = Left;
		m_moving = true;*/
		//startMove(Left);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		//m_sprite.move({ m_moveSpeed, 0 });	// right = {x, 0}
		m_direction = Vector2f(m_moveSpeed, 0);
		move();
		/*m_direction = Right;
		m_moving = true;*/
		//startMove(Right);
	}
}

//void Player::handleCollision(GameObject & obj)
//{
//}
//
//void Player::handleCollision(Player & player)
//{
//}
//
//void Player::handleCollision(NPC & npc)
//{
//}
//
//void Player::handleCollision(Map & map)
//{
//}
//
