#include "Animation.h"



Animation::Animation(GameObject & object, const Texture & texture, Vector2u imageCount, float speed)
	: m_object(object), m_imageCount(imageCount), m_speed(speed), m_totalTime(0.f),
	m_switchTime(50.f), m_currImage(Vector2u(0, 0)), m_forward(true)
{
	uvRect.width = texture.getSize().x / imageCount.x;
	uvRect.height = texture.getSize().y / imageCount.y;
}

Animation::~Animation()
{
}

void Animation::addAnimation(const string & name, unsigned row)
{
	m_animations[name] = row;
}

void Animation::play(const string & name)
{
	m_currImage.y = m_animations[name];
	m_totalTime += m_speed;

	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		if (m_currImage.x == m_imageCount.x - 1)
			m_forward = false;
		else if (m_currImage.x == 0)
			m_forward = true;

		m_currImage.x = m_forward ? m_currImage.x + 1 : m_currImage.x - 1;
	}
	uvRect.left = m_currImage.x * uvRect.width;
	uvRect.top = m_currImage.y * uvRect.height;
	m_object.setTextureRect(uvRect);
}
