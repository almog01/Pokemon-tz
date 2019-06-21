#include "Player.h"
#include "Map.h"
#include "Door.h"
#include "GameManager.h"

using sf::Keyboard;

Player::Player() : m_animation(*this, Resource::texture("player"), Vector2u(3, 4), 4.f)
{
	// initialize sprite
	m_sprite.setTexture(Resource::texture("player"), true);
	m_sprite.setTextureRect(sf::IntRect(16, 0, 16, 19));
	// add animation for each direction
	m_animation.addAnimation("down", 0);
	m_animation.addAnimation("up", 1);
	m_animation.addAnimation("right", 2);
	m_animation.addAnimation("left", 3);
	// initialize point of view
	m_pov.setSize(Vector2f(1.f, 1.f));
}

Player & Player::instance()
{
	static Player inst;
	return inst;
}

Player::~Player()
{
}

void Player::update(GameManager & gm)
{
	bool inGrass = false;
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		// update direction to up
		m_direction = Vector2f(0, -m_moveSpeed);	// up = {0, -y}
		// call move function
		move(inGrass);
		// play up animation
		m_animation.play("up");
		// update point of view
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(sizeX / 2, -sizeY / 8.f));
		// if moving inside grass, call game manager's wild pokemon battle function
		if (inGrass)
			gm.wildPokemonBattle();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		// update direction to down
		m_direction = Vector2f(0, m_moveSpeed);	// down = {0, y}
		// call move function
		move(inGrass);
		// play down animation
		m_animation.play("down");
		// update point of view
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(sizeX / 2, sizeY * 1.12f));
		// if moving inside grass, call game manager's wild pokemon battle function
		if (inGrass)
			gm.wildPokemonBattle();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// update direction to left
		m_direction = Vector2f(-m_moveSpeed, 0);	// left = {-x, 0}
		// call move function
		move(inGrass);
		// play left animation
		m_animation.play("left");
		// update point of view
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(-sizeX / 8, sizeY / 2));
		// if moving inside grass, call game manager's wild pokemon battle function
		if (inGrass)
			gm.wildPokemonBattle();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// update direction to right
		m_direction = Vector2f(m_moveSpeed, 0);	// right = {x, 0}
		// call move function
		move(inGrass);
		// play right animation
		m_animation.play("right");
		// update point of view
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(sizeX * 1.12f, sizeY / 2));
		// if moving inside grass, call game manager's wild pokemon battle function
		if (inGrass)
			gm.wildPokemonBattle();
	}
}

void Player::setMap(const Map * map)
{
	Character::setMap(map);		// call character's setMap func
	m_map = map->getName();		// and also save map name
}

void Player::handleCollision(Collider & collider)
{
	collider.handleCollision(*this);
}

void Player::handleCollision(Player & player)
{
}

void Player::handleCollision(NPC & npc)
{
	stop();		// stop when colliding with npc
}

void Player::handleCollision(Door & door)
{
	// when collidion with door, save the destination name and the new position 
	m_map = door.getDestination();
	m_sprite.setPosition(door.getDestPos());
}
