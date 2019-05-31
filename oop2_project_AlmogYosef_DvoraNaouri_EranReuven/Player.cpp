#include "Player.h"

using sf::Keyboard;

Player::Player() : m_animation(*this, Resource::texture("player"), Vector2u(3, 4), 3.75f)
{
	m_sprite.setTexture(Resource::texture("player"), true);
	m_sprite.setTextureRect(sf::IntRect(15, 0, 15, 19));
	m_animation.addAnimation("down", 0);
	m_animation.addAnimation("up", 1);
	m_animation.addAnimation("right", 2);
	m_animation.addAnimation("left", 3);
}


Player::~Player()
{
}

void Player::update()
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		m_direction = Vector2f(0, -m_moveSpeed);	// up = {0, -y}
		move();
		m_animation.play("up");
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		m_direction = Vector2f(0, m_moveSpeed);	// down = {0, y}
		move();
		m_animation.play("down");
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_direction = Vector2f(-m_moveSpeed, 0);	// left = {-x, 0}
		move();
		m_animation.play("left");
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_direction = Vector2f(m_moveSpeed, 0);	// right = {x, 0}
		move();
		m_animation.play("right");
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
